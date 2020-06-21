#include "StateDefinitions.h"
#include "../../Configuration.h"
#include "OSCompatibilityLayer.h"



std::set<int> Vic2::StateDefinitions::getAllProvinces(const int provinceNumber) const
{
	if (const auto mapping = stateMap.find(provinceNumber); mapping != stateMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::set<int>{};
	}
}


std::optional<std::string> Vic2::StateDefinitions::getStateID(const int provinceNumber) const
{
	if (const auto mapping = provinceToIDMap.find(provinceNumber); mapping != provinceToIDMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}


std::optional<int> Vic2::StateDefinitions::getCapitalProvince(const std::string& stateID) const
{
	if (const auto mapping = stateToCapitalMap.find(stateID); mapping != stateToCapitalMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}