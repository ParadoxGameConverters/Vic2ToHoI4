#include "HoI4AIStrategy.h"



HoI4::AIStrategy::AIStrategy(const std::string& strategyType,
	 const std::string& HoI4Tag,
	 const std::pair<int, std::vector<int>>& vic2StrategyData,
	 const States& states,
	 const Mappers::ProvinceMapper& provinceMapper):
	 type(strategyType),
	 id(HoI4Tag), value(vic2StrategyData.first)
{
	determineClaimedState(vic2StrategyData, states, provinceMapper);
}



HoI4::AIStrategy::AIStrategy(const Vic2::AIStrategy& oldStrategy, const std::string& HoI4Tag):
	 type(oldStrategy.getType()), id(HoI4Tag), value(oldStrategy.getValue())
{
	if (oldStrategy.getType() == "befriend")
	{
		type = "alliance";
		value = value / 2;
	}
	if (oldStrategy.getType() == "threat")
	{
		type = "contain";
	}
	if (oldStrategy.getType() == "rival")
	{
		type = "declare_war";
	}
}


void HoI4::AIStrategy::determineClaimedState(const std::pair<int, std::vector<int>>& vic2StrategyData,
	 const States& states,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	for (const auto& vic2Province: vic2StrategyData.second)
	{
		for (const auto& hoi4Province: provinceMapper.getVic2ToHoI4ProvinceMapping(vic2Province))
		{
			const auto& stateIdItr = states.getProvinceToStateIDMap().find(hoi4Province);
			if (stateIdItr == states.getProvinceToStateIDMap().end())
			{
				continue;
			}
			const auto& stateItr = states.getStates().find(stateIdItr->second);
			if (stateItr == states.getStates().end())
			{
				continue;
			}
			if (stateItr->second.getOwner() == id)
			{
				claimedState = stateIdItr->second;
				break;
			}
		}
		if (claimedState)
			break;
	}
}