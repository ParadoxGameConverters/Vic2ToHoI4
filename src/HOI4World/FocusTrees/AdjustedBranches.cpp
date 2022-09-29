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
	 const Maps::ProvinceDefinitions& provinceDefinitions):
	 mapUtils(mapUtils),
	 provinceToStateIdMapping(provinceToStateIdMapping), theMapData(theMapData), provinceDefinitions(provinceDefinitions)
{
	Log(LogLevel::Info) << "\tAdding adjusted focus branches";
	if (genericFocusTree.getBranches().contains("uk_colonial_focus"))
	{
		addUKColonialFocusBranch(countries, genericFocusTree, onActions);
	}
	if (genericFocusTree.getBranches().contains("FRA_begin_rearmament"))
	{
		addBeginRearmamentBranch(countries, genericFocusTree, onActions);
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

void HoI4::AdjustedBranches::determineGPZonesOfAccess(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	for (const auto& gp: greatPowers)
	{
		addToGPZoneOfAccess(gp, getNeighbors(gp, countries));
	}
}

void HoI4::AdjustedBranches::addToGPZoneOfAccess(const std::shared_ptr<Country>& gp,
	 const std::map<std::string, std::shared_ptr<Country>>& targetCountries)
{
	Log(LogLevel::Info) << "Adding countries to " << gp->getTag() << " zone of access";
	const auto& gpTag = gp->getTag();
	gpZonesOfAccess[gpTag].insert(gpTag);

	for (const auto& [tag, country]: targetCountries)
	{
		Log(LogLevel::Info) << " -> " << tag;
		const auto& relations = gp->getRelations(tag);
		if (!relations)
		{
			continue;
		}

		if (relations->hasMilitaryAccess() || gp->getPuppets().contains(tag))
		{
			gpZonesOfAccess[gpTag].insert(tag);
		}

		if (const auto& gpFaction = gp->getFaction(); gpFaction)
		{
			const auto& factionMembers = gpFaction->getMembers();
			if (std::find(factionMembers.begin(), factionMembers.end(), country) != factionMembers.end())
			{
				gpZonesOfAccess[gpTag].insert(tag);
			}
		}
	}
}

std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::AdjustedBranches::getNeighbors(
	 const std::shared_ptr<Country>& country,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	std::map<std::string, std::shared_ptr<Country>> neighbors;
	for (const auto& potentialNeighbor: countries)
	{
		if (countriesShareBorder(country, potentialNeighbor.second))
		{
			neighbors.emplace(potentialNeighbor);
		}
	}
	return neighbors;
}

void HoI4::AdjustedBranches::addBeginRearmamentBranch(std::map<std::string, std::shared_ptr<Country>> countries,
	 HoI4FocusTree& genericFocusTree,
	 OnActions& onActions)
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
	determineGPZonesOfAccess(greatPowers, countries);

	for (auto country: sortCountriesByStrength(countries))
	{
		Log(LogLevel::Debug) << "Checking " << country->getTag();
		if (country->getGovernmentIdeology() != "democratic")
		{
			Log(LogLevel::Debug) << " -> Not democratic";
			continue;
		}

		std::vector<std::shared_ptr<Country>> gpThreats;
		for (const auto& potentialAttacker: greatPowers)
		{
			const auto& potentialAttackerTag = potentialAttacker->getTag();
			if (potentialAttackerTag == country->getTag())
			{
				continue;
			}
			if (potentialAttacker->getGovernmentIdeology() == "democratic")
			{
				continue;
			}
			if (attackerCanPositionTroopsOnCountryBorders(country, potentialAttackerTag, countries) &&
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

bool HoI4::AdjustedBranches::countriesShareBorder(const std::shared_ptr<Country>& countryOne,
	 const std::shared_ptr<Country>& countryTwo)
{
	if (!mapUtils.findBorderStates(*countryOne, *countryTwo, provinceToStateIdMapping, theMapData, provinceDefinitions)
				.empty())
	{
		return true;
	}
	return false;
}

bool HoI4::AdjustedBranches::attackerCanPositionTroopsOnCountryBorders(const std::shared_ptr<Country>& country,
	 const std::string& attackerTag,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	for (const auto& gpAccessibleTag: gpZonesOfAccess[attackerTag])
	{
		const auto& gpAccessibleCountryItr = countries.find(gpAccessibleTag);
		if (gpAccessibleCountryItr == countries.end())
		{
			continue;
		}
		const auto& gpAccessibleCountry = gpAccessibleCountryItr->second;

		if (countriesShareBorder(country, gpAccessibleCountry))
			return true;
	}
	return false;
}