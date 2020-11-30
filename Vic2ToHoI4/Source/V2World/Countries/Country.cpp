#include "Country.h"
#include "V2World/Ai/Vic2AI.h"
#include "V2World/Ai/AIStrategy.h"
#include "V2World/Culture/CultureGroups.h"
#include "V2World/Diplomacy/Relations.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "StringUtils.h"
#include "V2World/Culture/CultureGroups.h"
#include "V2World/Diplomacy/Relations.h"
#include "V2World/Diplomacy/RelationsFactory.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Military/ArmyFactory.h"
#include "V2World/Military/Leaders/Leader.h"
#include "V2World/Politics/Party.h"
#include "V2World/Pops/Pop.h"
#include "V2World/Provinces/Province.h"
#include "V2World/States/State.h"
#include "V2World/States/StateDefinitions.h"
#include "V2World/States/StateFactory.h"
#include "V2World/Technology/Inventions.h"
#include <cmath>



void Vic2::Country::setParties(const std::vector<Party>& allParties)
{
	if (tag == "REB")
	{
		return;
	}
	for (auto ID: activePartyIDs)
	{
		if (ID <= allParties.size())
		{
			activeParties.insert(allParties.at(ID - 1)); // Subtract 1, because party ID starts from index of 1
		}
		else
		{
			Log(LogLevel::Warning) << "Party ID mismatch! Did some Vic2 country files not get read?";
		}
	}

	if (rulingPartyID == 0)
	{
		throw std::runtime_error(tag + " had no ruling party. The save needs manual repair.");
	}
	if (rulingPartyID > allParties.size())
	{
		throw std::runtime_error(
			 "Could not find the ruling party for " + tag + ". " + "Most likely a mod was not included.\n" +
			 "Double-check your settings, and remember to include EU4 to Vic2 mods. See the FAQ for more information.");
	}
	rulingParty =
		 std::make_unique<Party>(allParties.at(rulingPartyID - 1)); // Subtract 1, because party ID starts from index of 1
}


void Vic2::Country::eatCountry(Country& target, bool debug)
{
	if (target.tag == tag)
	{
		return;
	}

	for (auto& state: target.states)
	{
		state.setOwner(tag);
		states.push_back(std::move(state));
	}
	for (auto& core: target.cores)
	{
		core->addCore(tag);
		core->removeCore(target.tag);
		addCore(core);
	}
	for (auto& provinceItr: target.provinces)
	{
		provinceItr.second->setOwner(tag);
		provinces.insert(provinceItr);
	}
	technologiesAndInventions.insert(target.technologiesAndInventions.begin(), target.technologiesAndInventions.end());
	armies.insert(armies.end(), target.armies.begin(), target.armies.end());

	if (debug)
	{
		Log(LogLevel::Debug) << "Merged " << target.tag << " into " << tag;
	}
}


void Vic2::Country::putProvincesInStates()
{
	for (auto& state: states)
	{
		for (auto provinceNum: state.getProvinceNumbers())
		{
			auto province = provinces.find(provinceNum);
			if (province == provinces.end())
			{
				Log(LogLevel::Warning) << "State (" << state.getStateID() << ") owned by " << tag << " had province ("
											  << provinceNum << ") that " << tag << " did not";
				continue;
			}

			state.addProvince(province->second);
		}
	}
}


void Vic2::Country::limitCommanders()
{
	std::vector<Leader> generals;
	std::copy_if(leaders.begin(), leaders.end(), std::back_inserter(generals), [](const Leader& leader) {
		return leader.getType() == "land";
	});
	std::sort(generals.begin(), generals.end(), [](Leader& a, Leader& b) {
		return a.getPrestige() > b.getPrestige();
	});
	const int desiredGenerals = static_cast<int>(std::ceil(generals.size() / 20.0F));
	generals.erase(generals.begin() + desiredGenerals, generals.end());

	std::vector<Leader> admirals;
	std::copy_if(leaders.begin(), leaders.end(), std::back_inserter(admirals), [](const Leader& leader) {
		return leader.getType() == "sea";
	});
	std::sort(admirals.begin(), admirals.end(), [](Leader& a, Leader& b) {
		return a.getPrestige() > b.getPrestige();
	});
	const int desiredAdmirals = static_cast<int>(std::ceil(admirals.size() / 20.0F));
	admirals.erase(admirals.begin() + desiredAdmirals, admirals.end());

	leaders.clear();
	std::move(generals.begin(), generals.end(), std::back_inserter(leaders));
	std::move(admirals.begin(), admirals.end(), std::back_inserter(leaders));
}


void Vic2::Country::determineEmployedWorkers()
{
	for (auto& state: states)
	{
		state.determineEmployedWorkers();
	}
}


void Vic2::Country::setLocalisationNames(Localisations& vic2Localisations)
{
	if (!domainName.empty())
	{
		vic2Localisations.updateDomainCountry(tag, domainName);
	}
	auto nameInAllLanguages = vic2Localisations.getTextInEachLanguage(tag);
	for (auto nameInLanguage: nameInAllLanguages)
	{
		setLocalisationName(nameInLanguage.first, nameInLanguage.second);
	}
}


void Vic2::Country::setLocalisationName(const std::string& language, const std::string& name)
{
	if (!domainName.empty())
	{
		namesByLanguage[language] = domainName;
	}
	else if (!name.empty())
	{
		namesByLanguage[language] = name;
	}
}


void Vic2::Country::setLocalisationAdjectives(const Localisations& vic2Localisations)
{
	auto adjectiveInAllLanguages = vic2Localisations.getTextInEachLanguage(tag + "_ADJ");
	for (auto adjectiveinLanguage: adjectiveInAllLanguages)
	{
		setLocalisationAdjective(adjectiveinLanguage.first, adjectiveinLanguage.second);
	}
}


void Vic2::Country::setLocalisationAdjective(const std::string& language, const std::string& adjective)
{
	if (!domainAdjective.empty()) // Domains have their adjective set from domain_region
	{
		adjectivesByLanguage[language] = domainAdjective;
	}
	else if (!adjective.empty())
	{
		adjectivesByLanguage[language] = adjective;
	}
}


void Vic2::Country::handleMissingCulture(const CultureGroups& theCultureGroups)
{
	if (primaryCulture.empty())
	{
		auto cultureSizes = determineCultureSizes();
		primaryCulture = selectLargestCulture(cultureSizes);
		auto cultureGroupOption = theCultureGroups.getGroup(primaryCulture);
		if (cultureGroupOption)
		{
			primaryCultureGroup = *cultureGroupOption;
		}
		else
		{
			primaryCultureGroup = "no_culture";
		}
	}
}


std::map<std::string, int> Vic2::Country::determineCultureSizes()
{
	std::map<std::string, int> cultureSizes;

	for (auto [unused, province]: provinces)
	{
		for (auto pop: province->getPops())
		{
			std::string popCulture = pop.getCulture();
			auto cultureSize = cultureSizes.find(popCulture);
			if (cultureSize == cultureSizes.end())
			{
				cultureSizes.insert(make_pair(popCulture, 0));
				cultureSize = cultureSizes.find(popCulture);
			}
			cultureSize->second += pop.getSize();
		}
	}

	return cultureSizes;
}


std::string Vic2::Country::selectLargestCulture(const std::map<std::string, int>& cultureSizes)
{
	std::string largestCulture;
	int largestCultureSize = 0;
	for (auto cultureSize: cultureSizes)
	{
		if (cultureSize.second > largestCultureSize)
		{
			largestCulture = cultureSize.first;
			largestCultureSize = cultureSize.second;
		}
	}

	return largestCulture;
}


bool Vic2::Country::hasCoreOnCapital() const
{
	for (const auto& core: cores)
	{
		if (core->getNumber() == capital)
		{
			return true;
		}
	}

	return false;
}


int32_t Vic2::Country::getEmployedWorkers() const
{
	int32_t employedWorkers = 0;
	for (const auto& state: states)
	{
		employedWorkers += state.getEmployedWorkers();
	}

	return employedWorkers;
}


float Vic2::Country::getAverageIssueSupport(const std::string& issueName) const
{
	float totalPopulation = 0.0;
	float totalSupport = 0.0;
	for (const auto& [unused, province]: provinces)
	{
		for (const auto& pop: province->getPops())
		{
			const auto size = static_cast<float>(pop.getSize());
			totalSupport += pop.getIssueSupport(issueName) * size;
			totalPopulation += size;
		}
	}

	return totalSupport / totalPopulation;
}


bool Vic2::operator==(const Country& one, const Country& other)
{
	return one.getTag() == other.getTag();
}


std::optional<std::string> Vic2::Country::getName(const std::string& language) const
{
	if (const auto& nameInLanguage = namesByLanguage.find(language); nameInLanguage != namesByLanguage.end())
	{
		return nameInLanguage->second;
	}
	else
	{
		return std::nullopt;
	}
}


std::optional<std::string> Vic2::Country::getAdjective(const std::string& language) const
{
	if (const auto& adjectiveInLanguage = adjectivesByLanguage.find(language);
		 adjectiveInLanguage != adjectivesByLanguage.end())
	{
		return adjectiveInLanguage->second;
	}
	else
	{
		return std::nullopt;
	}
}


std::vector<std::string> Vic2::Country::getShipNames(const std::string& category) const
{
	const auto foundShipNames = shipNames.find(category);
	if (foundShipNames == shipNames.end())
	{
		return std::vector<std::string>{};
	}
	return foundShipNames->second;
}