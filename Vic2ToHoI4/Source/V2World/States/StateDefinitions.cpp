#include "StateDefinitions.h"
#include "OSCompatibilityLayer.h"



std::set<int> Vic2::StateDefinitions::getAllProvinces(const int provinceNumber) const
{
	if (!stateMap.contains(provinceNumber))
	{
		return std::set<int>{};
	}

	return stateMap.at(provinceNumber);
}


std::optional<std::string> Vic2::StateDefinitions::getStateID(const int provinceNumber) const
{
	if (!provinceToIDMap.contains(provinceNumber))
	{
		return std::nullopt;
	}

	return provinceToIDMap.at(provinceNumber);
}


std::optional<int> Vic2::StateDefinitions::getCapitalProvince(const std::string& stateID) const
{
	if (!stateToCapitalMap.contains(stateID))
	{
		return std::nullopt;
	}

	return stateToCapitalMap.at(stateID);
}