#include "AdjustedBranches.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/Characters/CharacterFactory.h"
#include "src/HOI4World/Characters/CharactersFactory.h"
#include "src/HOI4World/FocusTrees/AdjustedBranch.h"
#include "src/HOI4World/FocusTrees/FocusTreeFactory.h"
#include "src/HOI4World/HoI4Focus.h"
#include "src/HOI4World/HoI4FocusTree.h"
#include "src/HOI4World/Ideas/IdeaUpdaters.h"
#include "src/HOI4World/Ideas/IdeasFactory.h"
#include "src/HOI4World/WarCreator/MapUtils.h"
#include <algorithm>
#include <ranges>



HoI4::AdjustedBranches::AdjustedBranches(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::set<std::string>& majorIdeologies,
	 OnActions& onActions,
	 const HoI4::MapUtils& mapUtils,
	 const std::map<int, int>& provinceToStateIdMapping,
	 const Maps::MapData& theMapData,
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 Character::Factory& characterFactory,
	 Ideas& ideas):
	 mapUtils(mapUtils), provinceToStateIdMapping(provinceToStateIdMapping), theMapData(theMapData),
	 provinceDefinitions(provinceDefinitions)
{
	Log(LogLevel::Info) << "\tAdding adjusted focus branches";
	addUKColonialFocusBranch(countries, majorIdeologies, onActions);
	addBeginRearmamentBranch(countries, onActions);
	addPathOfMarxismLeninismBranch(countries, onActions);

	addIdeas(ideas, majorIdeologies);
}

void HoI4::AdjustedBranches::addUKColonialFocusBranch(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::set<std::string>& majorIdeologies,
	 OnActions& onActions)
{
	for (auto [tag, country]: countries)
	{
		if (country->isGreatPower() && country->getDominionTag("south_asia"))
		{
			const auto& theBranch = std::make_shared<AdjustedBranch>("uk_colonial_focus");
			theBranch->updateUKColonialFocuses(majorIdeologies);

			country->addAdjustedBranch(theBranch, "ENG", onActions);
			addedBranches.push_back(theBranch);
			break;
		}
	}
}

void HoI4::AdjustedBranches::addBeginRearmamentBranch(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 OnActions& onActions)
{
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
		if (country->getGovernmentIdeology() != "democratic")
		{
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
			const auto& relations = potentialAttacker->getRelations(country->getTag());
			if (!relations || (relations->getRelations() >= 0))
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
			const auto& theBranch = std::make_shared<AdjustedBranch>("FRA_begin_rearmament");

			country->addAdjustedBranch(theBranch, "FRA", onActions);
			addedBranches.push_back(theBranch);

			gpThreats[0]->addGlobalEventTarget("FRA_begin_rearmament_ITA");
			flagZoneOfAccess(gpThreats[0]->getTag(), "FRA_begin_rearmament_ITA_zone", countries);
			if (gpThreats.size() > 1)
			{
				gpThreats[1]->addGlobalEventTarget("FRA_begin_rearmament_GER");
				flagZoneOfAccess(gpThreats[1]->getTag(), "FRA_begin_rearmament_GER_zone", countries);
			}
			break;
		}
	}
}

void HoI4::AdjustedBranches::addPathOfMarxismLeninismBranch(
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 OnActions& onActions)
{
	for (auto [tag, country]: countries)
	{
		if (country->isGreatPower() && country->getGovernmentIdeology() == "communism")
		{
			const auto& theBranch = std::make_shared<AdjustedBranch>("SOV_the_path_of_marxism_leninism");

			country->addAdjustedBranch(theBranch, "SOV", onActions);
			addedBranches.push_back(theBranch);
			break;
		}
	}
}


void HoI4::AdjustedBranches::addIdeas(Ideas& ideas, const std::set<std::string>& majorIdeologies)
{
	for (const auto& addedBranch: addedBranches)
	{
		for (auto ideaGroup: addedBranch->getIdeas().getGeneralIdeas())
		{
			updateGeneralIdeas(ideaGroup, majorIdeologies);
			ideas.addGeneralIdeas(ideaGroup);
		}
	}
}

void HoI4::AdjustedBranches::determineGPZonesOfAccess(const std::vector<std::shared_ptr<Country>>& greatPowers,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	for (const auto& gp: greatPowers)
	{
		gpZonesOfAccess[gp->getTag()].insert(gp->getTag()); // adding self
		addCountriesToGPZoneOfAccess(gp, gp, countries);
	}
}

void HoI4::AdjustedBranches::addCountriesToGPZoneOfAccess(const std::shared_ptr<Country>& gp,
	 const std::shared_ptr<Country>& referenceCountry,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	for (const auto& [tag, country]: getNeighbors(referenceCountry, countries))
	{
		const auto& relations = gp->getRelations(tag);
		if (!relations)
		{
			continue;
		}

		if (relations->hasMilitaryAccess() || gp->getPuppets().contains(tag))
		{
			addToGPZoneOfAccess(gp, country, countries);
		}

		if (const auto& gpFaction = gp->getFaction(); gpFaction)
		{
			const auto& factionMembers = gpFaction->getMembers();
			if (std::find(factionMembers.begin(), factionMembers.end(), country) != factionMembers.end())
			{
				addToGPZoneOfAccess(gp, country, countries);
			}
		}
	}
}

void HoI4::AdjustedBranches::addToGPZoneOfAccess(const std::shared_ptr<Country>& gp,
	 const std::shared_ptr<Country>& country,
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	if (gpZonesOfAccess[gp->getTag()].contains(country->getTag()))
	{
		return;
	}

	gpZonesOfAccess[gp->getTag()].insert(country->getTag());
	addCountriesToGPZoneOfAccess(gp, country, countries);
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

void HoI4::AdjustedBranches::flagZoneOfAccess(const std::string& gpTag,
	 const std::string& flag,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	for (const auto& tag: gpZonesOfAccess[gpTag])
	{
		if (!countries.contains(tag))
			continue;

		if (const auto& country = countries.at(tag); country)
		{
			country->setFlag(flag);
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