#include "StateFactory.h"
#include "BuildingReader.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include "StateDefinitions.h"



Vic2::State::Factory::Factory()
{
	registerKeyword("provinces", [this](std::istream& theStream) {
		auto provinces = commonItems::intList{theStream}.getInts();
		state->provinceNumbers.insert(provinces.begin(), provinces.end());
	});
	registerKeyword("state_buildings", [this](std::istream& theStream) {
		state->factoryLevel += buildingReader.getLevel(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::State> Vic2::State::Factory::getState(std::istream& theStream,
	 const std::string& ownerTag,
	 const StateDefinitions& theStateDefinitions)
{
	state = std::make_unique<State>();

	state->owner = ownerTag;
	parseStream(theStream);
	setID(theStateDefinitions);
	determineIfPartialState(theStateDefinitions);
	setCapital(theStateDefinitions);

	return std::move(state);
}


std::unique_ptr<Vic2::State> Vic2::State::Factory::getUnownedState(
	 const std::unordered_map<int, std::shared_ptr<Province>>& theProvinces,
	 const StateDefinitions& theStateDefinitions)
{
	state = std::make_unique<State>();

	for (const auto& [provinceNum, province]: theProvinces)
	{
		state->provinceNumbers.insert(provinceNum);
		state->provinces.push_back(province);
	}
	setID(theStateDefinitions);
	determineIfPartialState(theStateDefinitions);
	setCapital(theStateDefinitions);

	return std::move(state);
}


void Vic2::State::Factory::setID(const StateDefinitions& theStateDefinitions) const
{
	const auto& provinceNumbers = state->provinceNumbers;
	if (provinceNumbers.empty())
	{
		return;
	}

	if (auto foundStateID = theStateDefinitions.getStateID(*provinceNumbers.begin()); foundStateID)
	{
		state->stateID = *foundStateID;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not find the state for Vic2 province " << *provinceNumbers.begin() << ".";
	}
}


void Vic2::State::Factory::setCapital(const StateDefinitions& theStateDefinitions) const
{
	state->capitalProvince = theStateDefinitions.getCapitalProvince(state->stateID);
}


void Vic2::State::Factory::determineIfPartialState(const StateDefinitions& theStateDefinitions) const
{
	const auto& provinceNumbers = state->provinceNumbers;
	if (provinceNumbers.empty())
	{
		return;
	}

	for (auto expectedProvince: theStateDefinitions.getAllProvinces(*provinceNumbers.begin()))
	{
		if (!provinceNumbers.contains(expectedProvince))
		{
			state->partialState = true;
			break;
		}
	}
}