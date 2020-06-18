#include "StateFactory.h"
#include "BuildingReader.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "StateDefinitions.h"



Vic2::State::Factory::Factory()
{
	registerKeyword("provinces", [this](const std::string& unused, std::istream& theStream) {
		for (auto province: commonItems::intList{theStream}.getInts())
		{
			state->provinceNumbers.insert(province);
		}
	});
	registerKeyword("state_buildings", [this](const std::string& unused, std::istream& theStream) {
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
	 const std::set<std::pair<int, std::shared_ptr<Province>>>& theProvinces,
	 const StateDefinitions& theStateDefinitions)
{
	state = std::make_unique<State>();

	for (const auto& province: theProvinces)
	{
		state->provinceNumbers.insert(province.first);
		state->provinces.insert(province.second);
	}
	setID(theStateDefinitions);
	determineIfPartialState(theStateDefinitions);
	setCapital(theStateDefinitions);

	return std::move(state);
}


void Vic2::State::Factory::setID(const StateDefinitions& theStateDefinitions) const
{
	auto foundStateID = theStateDefinitions.getStateID(*state->provinceNumbers.begin());
	if (foundStateID)
	{
		state->stateID = *foundStateID;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not find the state for Vic2 province " << *state->provinceNumbers.begin() << ".";
	}
}


void Vic2::State::Factory::setCapital(const StateDefinitions& theStateDefinitions) const
{
	state->capitalProvince = theStateDefinitions.getCapitalProvince(state->stateID);
}


void Vic2::State::Factory::determineIfPartialState(const StateDefinitions& theStateDefinitions) const
{
	if (state->provinces.size() > 0)
	{
		for (auto expectedProvince: theStateDefinitions.getAllProvinces(*state->provinceNumbers.begin()))
		{
			if (state->provinceNumbers.count(expectedProvince) == 0)
			{
				state->partialState = true;
				break;
			}
		}
	}
}