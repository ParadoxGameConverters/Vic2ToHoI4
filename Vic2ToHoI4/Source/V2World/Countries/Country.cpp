#include "Country.h"
#include "Log.h"
#include "V2World/Culture/CultureGroups.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Pops/Pop.h"
#include "V2World/Provinces/Province.h"
#include "V2World/States/State.h"
#include <ranges>



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


void Vic2::Country::mergeStates(const StateDefinitions& stateDefinitions)
{
	for (auto state = states.begin(); state != states.end(); ++state)
	{
		if (!state->isPartialState())
		{
			continue;
		}

		auto state2 = state;
		++state2;
		while (state2 != states.end())
		{
			if (state->getStateID() != state2->getStateID())
			{
				++state2;
				continue;
			}

			state->eatState(*state2, stateDefinitions);
			state2 = states.erase(state2);
		}
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
	for (const auto& [language, name]: nameInAllLanguages)
	{
		setLocalisationName(language, name);
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
	for (const auto& [language, adjective]: adjectiveInAllLanguages)
	{
		setLocalisationAdjective(language, adjective);
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
	if (primaryCulture == "no_culture")
	{
		const auto cultureSizes = determineCultureSizes();
		primaryCulture = selectLargestCulture(cultureSizes);
		auto cultureGroupOption = theCultureGroups.getGroup(primaryCulture);
		if (cultureGroupOption)
		{
			primaryCultureGroup = *cultureGroupOption;
		}
	}
}


std::map<std::string, int> Vic2::Country::determineCultureSizes()
{
	std::map<std::string, int> cultureSizes;

	for (auto province : provinces | std::views::values)
	{
		for (const auto& pop: province->getPops())
		{
			const auto& popSize = pop.getSize();
			const auto& popCulture = pop.getCulture();
			auto [existing, inserted] = cultureSizes.insert(std::make_pair(popCulture, popSize));
			if (!inserted)
			{
				existing->second += pop.getSize();
			}
		}
	}

	return cultureSizes;
}


std::string Vic2::Country::selectLargestCulture(const std::map<std::string, int>& cultureSizes)
{
	std::string largestCulture = "no_culture";
	auto largestCultureSize = 0;
	for (const auto& [culture, size]: cultureSizes)
	{
		if (size > largestCultureSize)
		{
			largestCulture = culture;
			largestCultureSize = size;
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
	for (const auto& province : provinces | std::views::values)
	{
		for (const auto& pop: province->getPops())
		{
			const auto size = static_cast<float>(pop.getSize());
			totalSupport += pop.getIssueSupport(issueName) * size;
			totalPopulation += size;
		}
	}

	if (totalPopulation == 0.0F)
	{
		return 0.0F;
	}

	return totalSupport / totalPopulation;
}


bool Vic2::operator==(const Country& one, const Country& other)
{
	return one.getTag() == other.getTag();
}


std::optional<std::string> Vic2::Country::getName(const std::string& language) const
{
	const auto& nameInLanguage = namesByLanguage.find(language);
	if (nameInLanguage == namesByLanguage.end())
	{
		return std::nullopt;
	}

	return nameInLanguage->second;
}


std::optional<std::string> Vic2::Country::getAdjective(const std::string& language) const
{
	const auto& adjectiveInLanguage = adjectivesByLanguage.find(language);
	if (adjectiveInLanguage == adjectivesByLanguage.end())
	{
		return std::nullopt;
	}

	return adjectiveInLanguage->second;
}


std::vector<std::string> Vic2::Country::getShipNames(const std::string& category) const
{
	const auto foundShipNames = shipNames.find(category);
	if (foundShipNames == shipNames.end())
	{
		return {};
	}
	return foundShipNames->second;
}