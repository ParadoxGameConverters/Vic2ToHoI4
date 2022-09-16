#include "src/HOI4World/Map/SupplyNodes.h"
#include "src/HOI4World/States/HoI4States.h"

std::set<int> HoI4::determineSupplyNodes(const std::map<int, State>& states, const std::set<int>& railwayEndpoints)
{
	std::set<int> supplyNodes;
	for (const auto& state: states)
	{
		if (state.second.isImpassable())
		{
			continue;
		}
		int SupplyNodesInState = 0;
		int maxAllowedSupplyNodes =
			 std::max(1, static_cast<int>(std::floor(static_cast<double>(state.second.getProvinces().size()) / 6.0)));
		for (const auto& province: state.second.getProvinces())
		{
			if (railwayEndpoints.contains(province))
			{
				supplyNodes.insert(province);
				SupplyNodesInState++;
			}
			if (SupplyNodesInState == maxAllowedSupplyNodes)
			{
				break;
			}
		}
	}

	return supplyNodes;
}