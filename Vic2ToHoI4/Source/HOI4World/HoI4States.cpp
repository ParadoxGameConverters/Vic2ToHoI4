/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "HoI4States.h"
#include "ImpassableProvinces.h"
#include "HoI4State.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/ProvinceDefinitions.h"
#include "../Mappers/V2Localisations.h"
#include "../V2World/Country.h"
#include "../V2World/Province.h"
#include "../V2World/State.h"
#include "../V2World/StateDefinitions.h"
#include "../V2World/World.h"
#include <fstream>



HoI4States::HoI4States(const Vic2::World* _sourceWorld, const CountryMapper& countryMap):
	sourceWorld(_sourceWorld),
	ownersMap(),
	coresMap(),
	assignedProvinces(),
	states(),
	provinceToStateIDMap()
{
	int num;

	LOG(LogLevel::Info) << "Converting states";
	registerKeyword(std::regex("state"), [this, &num](const std::string& unused, std::istream& theStream){
		defaultStates.insert(make_pair(num, new HoI4::State(theStream)));
	});

	LOG(LogLevel::Info) << "Finding impassable provinces";

	std::set<std::string> statesFiles;
	Utils::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/history/states", statesFiles);
	for (auto stateFile: statesFiles)
	{
		num = stoi(stateFile.substr(0, stateFile.find_first_of('-')));
		parseFile(theConfiguration.getHoI4Path() + "/history/states/" + stateFile);
	}

	HoI4::impassableProvinces theImpassables(defaultStates);

	determineOwnersAndCores(countryMap);
	createStates(theImpassables, countryMap);
}


void HoI4States::determineOwnersAndCores(const CountryMapper& countryMap)
{
	for (auto provinceNumber: provinceDefinitions::getLandProvinces())
	{
		auto sourceProvinceNums = retrieveSourceProvinceNums(provinceNumber);
		if (sourceProvinceNums)
		{
			auto potentialOwners = determinePotentialOwners(*sourceProvinceNums);
			if (potentialOwners.size() == 0)
			{
				ownersMap.insert(make_pair(provinceNumber, ""));
				continue;
			}
			auto oldOwner = selectProvinceOwner(potentialOwners);


			auto HoI4Tag = countryMap.getHoI4Tag(oldOwner);
			if (!HoI4Tag)
			{
				LOG(LogLevel::Warning)
					<< "Could not map states owned by " << oldOwner << " in Vic2, as there is no mathcing HoI4 country.";
				continue;
			}
			ownersMap.insert(make_pair(provinceNumber, *HoI4Tag));

			vector<string> cores = determineCores(*sourceProvinceNums, oldOwner, countryMap, *HoI4Tag);
			coresMap.insert(make_pair(provinceNumber, cores));
		}
	}
}


optional<vector<int>> HoI4States::retrieveSourceProvinceNums(int provNum) const
{
	auto provinceLink = theProvinceMapper.getHoI4ToVic2ProvinceMapping(provNum);
	if (provinceLink && (provinceLink->size() > 0))
	{
		if ((*provinceLink)[0] == 0)
		{
			return std::nullopt;
		}
		else
		{
			return provinceLink;
		}
	}
	else
	{
		LOG(LogLevel::Warning) << "No source for HoI4 land province " << provNum;
		return std::nullopt;
	}
}


const std::map<std::string, std::pair<int, int>> HoI4States::determinePotentialOwners(
	const std::vector<int>& sourceProvinceNums
) const {
	std::map<std::string, std::pair<int, int>> potentialOwners;

	for (auto srcProvNum: sourceProvinceNums)
	{
		auto srcProvince = sourceWorld->getProvince(srcProvNum);
		if (!srcProvince)
		{
			LOG(LogLevel::Warning) << "Old province " << srcProvNum << " does not exist (bad mapping?)";
			continue;
		}
		auto owner = (*srcProvince)->getOwner();
		if (owner == "")
		{
			continue;
		}

		if (potentialOwners.find(owner) == potentialOwners.end())
		{
			potentialOwners[owner] = make_pair(0, 0);
		}
		potentialOwners[owner].first++;
		potentialOwners[owner].second += (*srcProvince)->getTotalPopulation();
	}

	return potentialOwners;
}


const std::string HoI4States::selectProvinceOwner(
	const std::map<std::string, std::pair<int, int>>& potentialOwners
) const {
	std::string oldOwner;
	for (auto potentialOwner: potentialOwners)
	{
		// I am the new owner if there is no current owner, or I have more provinces than the current owner,
		// or I have the same number of provinces, but more population, than the current owner
		if (	(oldOwner == "") ||
				(potentialOwner.second.first > potentialOwners.find(oldOwner)->second.first) ||
				(
					(potentialOwner.second.first == potentialOwners.find(oldOwner)->second.first) &&
					(potentialOwner.second.second > potentialOwners.find(oldOwner)->second.second)
				)
			)
		{
			oldOwner = potentialOwner.first;
		}
	}

	return oldOwner;
}


std::vector<std::string> HoI4States::determineCores(
	const std::vector<int>& sourceProvinces,
	const std::string& Vic2Owner,
	const CountryMapper& countryMap,
	const std::string& newOwner
) const {
	std::vector<std::string> cores;

	for (auto sourceProvinceNum: sourceProvinces)
	{
		auto sourceProvince = sourceWorld->getProvince(sourceProvinceNum);
		if (!sourceProvince)
		{
			continue;
		}

		for (auto Vic2Core: (*sourceProvince)->getCores())
		{
			auto HoI4CoreTag = countryMap.getHoI4Tag(Vic2Core);
			if (HoI4CoreTag)
			{
				// skip this core if the country is the owner of the V2 province but not the HoI4 province
				// (i.e. "avoid boundary conflicts that didn't exist in V2").
				// this country may still get core via a province that DID belong to the current HoI4 owner
				if ((Vic2Core == Vic2Owner) && (*HoI4CoreTag != newOwner))
				{
					continue;
				}

				cores.push_back(*HoI4CoreTag);
			}
		}
	}

	return cores;
}


void HoI4States::createStates(const HoI4::impassableProvinces& theImpassables, const CountryMapper& countryMap)
{
	std::set<int> ownedProvinces;

	for (auto country: sourceWorld->getCountries())
	{
		for (auto vic2State: country.second->getStates())
		{
			auto possibleHoI4Owner = countryMap.getHoI4Tag(country.first);
			if (possibleHoI4Owner)
			{
				createMatchingHoI4State(vic2State, *possibleHoI4Owner, theImpassables);
				for (auto province: vic2State->getProvinces())
				{
					ownedProvinces.insert(province->getNumber());
				}
			}
		}
	}

	std::map<int, Vic2::Province*> unownedProvinces;
	for (auto vic2Province: sourceWorld->getProvinces())
	{
		if (ownedProvinces.count(vic2Province.first) == 0)
		{
			unownedProvinces.insert(vic2Province);
		}
	}

	while (unownedProvinces.size() > 0)
	{
		std::set<std::pair<int, Vic2::Province*>> stateProvinces;

		auto stateProvinceNums = Vic2::theStateDefinitions.getAllProvinces(unownedProvinces.begin()->first);
		if (stateProvinceNums.size() == 0)
		{
			unownedProvinces.erase(unownedProvinces.begin());
			continue;
		}
		for (auto provinceNum: stateProvinceNums)
		{
			auto province = unownedProvinces.find(provinceNum);
			if (province != unownedProvinces.end())
			{
				stateProvinces.insert(*province);
				unownedProvinces.erase(province);
			}
		}

		Vic2::State* newState = new Vic2::State(stateProvinces);
		createMatchingHoI4State(newState, "", theImpassables);
	}

	unsigned int manpower = getTotalManpower();
	LOG(LogLevel::Debug) << "Total manpower was " << manpower << ", which is " << manpower / 20438756.2 << "% of default HoI4.";
}


void HoI4States::createMatchingHoI4State(const Vic2::State* vic2State, const string& stateOwner, const HoI4::impassableProvinces& theImpassables)
{
	unordered_set<int> passableProvinces;
	unordered_set<int> impassableProvinces;
	auto allProvinces = getProvincesInState(vic2State, stateOwner);
	for (auto province: allProvinces)
	{
		if (theImpassables.isProvinceImpassable(province))
		{
			impassableProvinces.insert(province);
		}
		else
		{
			passableProvinces.insert(province);
		}
	}

	if (passableProvinces.size() > 0)
	{
		HoI4::State* newState = new HoI4::State(vic2State, nextStateID, stateOwner);
		if (impassableProvinces.size() > 0)
		{
			newState->markHadImpassablePart();
		}
		addProvincesAndCoresToNewState(newState, passableProvinces);
		newState->tryToCreateVP();
		newState->addManpower();
		states.insert(make_pair(nextStateID, newState));
		nextStateID++;
	}

	if (impassableProvinces.size() > 0)
	{
		HoI4::State* newState = new HoI4::State(vic2State, nextStateID, stateOwner);
		addProvincesAndCoresToNewState(newState, impassableProvinces);
		newState->makeImpassable();
		newState->tryToCreateVP();
		newState->addManpower();
		states.insert(make_pair(nextStateID, newState));
		nextStateID++;
	}
}


unordered_set<int> HoI4States::getProvincesInState(const Vic2::State* vic2State, const string& owner)
{
	unordered_set<int> provinces;
	for (auto vic2ProvinceNum: vic2State->getProvinceNums())
	{
		if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(vic2ProvinceNum))
		{
			for (auto HoI4ProvNum: *mapping)
			{
				if (
						isProvinceValid(HoI4ProvNum) &&
						isProvinceOwnedByCountry(HoI4ProvNum, owner) &&
						isProvinceNotAlreadyAssigned(HoI4ProvNum)
					)

				{
					provinces.insert(HoI4ProvNum);
					assignedProvinces.insert(HoI4ProvNum);
				}
			}
		}
	}

	return provinces;
}


void HoI4States::addProvincesAndCoresToNewState(HoI4::State* newState, unordered_set<int> provinces)
{
	for (auto province: provinces)
	{
		newState->addProvince(province);
		provinceToStateIDMap.insert(make_pair(province, newState->getID()));
		auto coresMapping = coresMap.find(province);
		if (coresMapping != coresMap.end())
		{
			newState->addCores(coresMap.find(province)->second);
		}
	}
}


bool HoI4States::isProvinceValid(int provNum) const
{
	if (provNum == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool HoI4States::isProvinceOwnedByCountry(int provNum, const string& stateOwner) const
{
	auto provinceOwnerItr = ownersMap.find(provNum);
	if ((provinceOwnerItr == ownersMap.end()) || (provinceOwnerItr->second != stateOwner))
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool HoI4States::isProvinceNotAlreadyAssigned(int provNum) const
{
	if ((assignedProvinces.find(provNum) != assignedProvinces.end()))
	{
		return false;
	}
	else
	{
		return true;
	}
}


unsigned int HoI4States::getTotalManpower() const
{
	unsigned int totalManpower = 0;
	for (auto state: states)
	{
		totalManpower += state.second->getManpower();
	}

	return totalManpower;
}


void HoI4States::output() const
{
	LOG(LogLevel::Debug) << "Writing states";

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history/states"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history/states";
		exit(-1);
	}
	for (auto state: states)
	{
		state.second->output(to_string(state.first) + ".txt");
	}
}