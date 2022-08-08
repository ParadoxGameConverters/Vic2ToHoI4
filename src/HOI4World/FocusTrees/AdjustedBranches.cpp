#include "AdjustedBranches.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/WarCreator/MapUtils.h"
#include <ranges>



HoI4::AdjustedBranches::AdjustedBranches(std::map<std::string, std::shared_ptr<Country>> countries,
	 HoI4FocusTree& genericFocusTree,
	 OnActions& onActions,
	 const HoI4::MapUtils& mapUtils,
	 const std::map<int, int>& provinceToStateIdMapping,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions)
{
	Log(LogLevel::Info) << "\tAdding adjusted focus branches";
	if (genericFocusTree.getBranches().contains("uk_colonial_focus"))
	{
		addUKColonialFocusBranch(countries, genericFocusTree, onActions);
	}
	if (genericFocusTree.getBranches().contains("FRA_begin_rearmament"))
	{
		addBeginRearmamentBranch(countries,
			 genericFocusTree,
			 onActions,
			 mapUtils,
			 provinceToStateIdMapping,
			 theMapData,
			 provinceDefinitions);
	}
}

void HoI4::AdjustedBranches::addUKColonialFocusBranch(std::map<std::string, std::shared_ptr<Country>> countries,
	 HoI4FocusTree& genericFocusTree,
	 OnActions& onActions)
{
	for (auto [tag, country]: countries)
	{
		if (country->isGreatPower() && country->getDominionTag("south_asia"))
		{
			country->addGlobalEventTarget("uk_colonial_focus_ENG");
			country->addFocusTreeBranch("uk_colonial_focus", onActions);
			genericFocusTree.eraseBranch("uk_colonial_focus");
			branchNames.push_back("uk_colonial_focus");
		}
	}
}

void HoI4::AdjustedBranches::addBeginRearmamentBranch(std::map<std::string, std::shared_ptr<Country>> countries,
	 HoI4FocusTree& genericFocusTree,
	 OnActions& onActions,
	 const HoI4::MapUtils& mapUtils,
	 const std::map<int, int>& provinceToStateIdMapping,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions)
{
	Log(LogLevel::Info) << " -> Adding \"Begin Rearmament\" branch";
	std::vector<std::shared_ptr<Country>> greatPowers;
	for (const auto& country: countries | std::views::values)
	{
		if (country->isGreatPower())
		{
			greatPowers.push_back(country);
		}
	}

	for (auto country: greatPowers)
	{
		if (country->getGovernmentIdeology() != "democratic")
		{
			continue;
		}

		std::vector<std::shared_ptr<Country>> neighbors;
		for (const auto& potentialNeighbor: greatPowers)
		{
			if (potentialNeighbor->getTag() == country->getTag())
			{
				continue;
			}
			if (potentialNeighbor->getGovernmentIdeology() == "democratic")
			{
				continue;
			}
			if (const auto& borderStates = mapUtils
						.findBorderStates(*country,
							 *potentialNeighbor,
							 provinceToStateIdMapping,
							 theMapData,
							 provinceDefinitions);
						!borderStates.empty() &&
				 neighbors.size() < 3)
			{
				Log(LogLevel::Info) << "\t" << potentialNeighbor->getTag();
				for (const auto& state: borderStates)
				{
					Log(LogLevel::Info) << "\t\t" << state;
				}
				neighbors.push_back(potentialNeighbor);
			}
		}

		if (!neighbors.empty())
		{
			Log(LogLevel::Info) << "\t\tFrance: " << country->getTag();
			country->addGlobalEventTarget("FRA_begin_rearmament_FRA");
			Log(LogLevel::Info) << "\t\tItaly: " << neighbors[0]->getTag();
			neighbors[0]->addGlobalEventTarget("FRA_begin_rearmament_ITA");
			if (neighbors.size() > 1)
			{
				Log(LogLevel::Info) << "\t\tGermany: " << neighbors[1]->getTag();
				neighbors[1]->addGlobalEventTarget("FRA_begin_rearmament_GER");
			}
			country->addFocusTreeBranch("FRA_begin_rearmament", onActions);
			branchNames.push_back("FRA_begin_rearmament");
		}
	}
}