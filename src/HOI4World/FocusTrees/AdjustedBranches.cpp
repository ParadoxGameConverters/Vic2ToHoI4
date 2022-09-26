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
			break;
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

	for (auto country: sortCountriesByStrength(countries))
	{
		if (country->getGovernmentIdeology() != "democratic")
		{
			continue;
		}

		std::vector<std::shared_ptr<Country>> gpThreats;
		for (const auto& potentialAttacker: greatPowers)
		{
			if (potentialAttacker->getTag() == country->getTag())
			{
				continue;
			}
			if (potentialAttacker->getGovernmentIdeology() == "democratic")
			{
				continue;
			}
			if (attackerCanPositionTroopsOnCountryBorders(country,
					  potentialAttacker,
					  mapUtils,
					  provinceToStateIdMapping,
					  theMapData,
					  provinceDefinitions) &&
				 gpThreats.size() < 3)
			{
				gpThreats.push_back(potentialAttacker);
			}
		}

		if (!gpThreats.empty())
		{
			Log(LogLevel::Info) << "\t\tFrance: " << country->getTag();
			country->addGlobalEventTarget("FRA_begin_rearmament_FRA");
			Log(LogLevel::Info) << "\t\tItaly: " << gpThreats[0]->getTag();
			gpThreats[0]->addGlobalEventTarget("FRA_begin_rearmament_ITA");
			if (gpThreats.size() > 1)
			{
				Log(LogLevel::Info) << "\t\tGermany: " << gpThreats[1]->getTag();
				gpThreats[1]->addGlobalEventTarget("FRA_begin_rearmament_GER");
			}
			country->addFocusTreeBranch("FRA_begin_rearmament", onActions);
			branchNames.push_back("FRA_begin_rearmament");
			break;
		}
	}
}

std::vector<std::shared_ptr<HoI4::Country>> HoI4::AdjustedBranches::sortCountriesByStrength(
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	std::vector<std::shared_ptr<Country>> sortedCountries;

	for (const auto& country: countries | std::views::values)
	{
		if (country->isGreatPower())
		{
			sortedCountries.push_back(country);
		}
	}

	std::vector<std::shared_ptr<Country>> nonGPs;
	for (const auto& country: countries | std::views::values)
	{
		if (!country->isGreatPower())
		{
			nonGPs.push_back(country);
		}
	}
	std::ranges::sort(nonGPs, [](const std::shared_ptr<Country>& a, const std::shared_ptr<Country>& b) {
		return a->getStrengthOverTime(1.0) > b->getStrengthOverTime(3.0);
	});

	for (const auto& country: nonGPs)
	{
		sortedCountries.push_back(country);
	}

	return sortedCountries;
}

bool HoI4::AdjustedBranches::attackerCanPositionTroopsOnCountryBorders(const std::shared_ptr<Country>& country,
	 const std::shared_ptr<Country>& attacker,
	 const HoI4::MapUtils& mapUtils,
	 const std::map<int, int>& provinceToStateIdMapping,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions)
{
	Log(LogLevel::Debug) << "\tChecking if " << attacker->getTag() << " can position troops on " << country->getTag()
								<< " borders";
	if (!mapUtils.findBorderStates(*country, *attacker, provinceToStateIdMapping, theMapData, provinceDefinitions)
				.empty())
		return true;

	if (!attacker->getFaction())
	{
		return false;
	}

	// Checking faction members because of military access they give; TODO: countries explicitly giving MA
	for (const auto& enemy: attacker->getFaction()->getMembers())
	{
		if (enemy->getTag() == attacker->getTag())
		{
			continue;
		}
		if (!attackerCanPositionTroopsOnCountryBorders(enemy, attacker, mapUtils, provinceToStateIdMapping, theMapData, provinceDefinitions))
		{
			Log(LogLevel::Debug) << " -> does not border " << attacker->getTag();
			continue;
		}

		if (attackerCanPositionTroopsOnCountryBorders(country, enemy, mapUtils, provinceToStateIdMapping, theMapData, provinceDefinitions))
			return true;
	}
	return false;
}