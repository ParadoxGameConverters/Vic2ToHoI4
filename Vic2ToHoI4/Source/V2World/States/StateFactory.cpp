#include "StateFactory.h"
#include "../Building.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "StateDefinitions.h"



Vic2::State::Factory::Factory()
{
	registerKeyword("provinces", [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList provinceList(theStream);
		for (auto province: provinceList.getInts())
		{
			state->provinceNumbers.insert(province);
		}
	});
	registerKeyword("state_buildings", [this](const std::string& unused, std::istream& theStream) {
		Building theBuilding(theStream);
		state->factoryLevel += theBuilding.getLevel();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}



std::unique_ptr<Vic2::State> Vic2::State::Factory::getState(std::istream& theStream,
	 const std::string& ownerTag,
	 const Vic2::StateDefinitions& theStateDefinitions)
{
	state = std::make_unique<State>();

	state->owner = ownerTag;

	parseStream(theStream);
	setID(theStateDefinitions);
	determineIfPartialState(theStateDefinitions);
	setCapital(theStateDefinitions);

	return std::move(state);
}


std::unique_ptr<Vic2::State> Vic2::State::Factory::getState(
	 std::set<std::pair<int, std::shared_ptr<Vic2::Province>>> theProvinces,
	 const StateDefinitions& theStateDefinitions)
{
	state = std::make_unique<State>();

	for (auto province: theProvinces)
	{
		state->provinceNumbers.insert(province.first);
		state->provinces.insert(province.second);
	}
	setID(theStateDefinitions);
	determineIfPartialState(theStateDefinitions);
	setCapital(theStateDefinitions);

	return std::move(state);
}


void Vic2::State::Factory::setID(const Vic2::StateDefinitions& theStateDefinitions)
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


void Vic2::State::Factory::setCapital(const Vic2::StateDefinitions& theStateDefinitions)
{
	state->capitalProvince = theStateDefinitions.getCapitalProvince(state->stateID);
}


void Vic2::State::Factory::determineIfPartialState(const StateDefinitions& theStateDefinitions)
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