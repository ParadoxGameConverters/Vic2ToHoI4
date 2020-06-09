#include "Country.h"
#include "CultureGroups.h"
#include "Inventions.h"
#include "Leader.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "Party.h"
#include "Pops/Pop.h"
#include "Province.h"
#include "Relations.h"
#include "State.h"
#include "StateDefinitions.h"
#include "StringUtils.h"
#include "Vic2Localisations.h"



Vic2::Country::Country(const std::string& theTag,
	 std::istream& theStream,
	 const inventions& theInventions,
	 const cultureGroups& theCultureGroups,
	 const StateDefinitions& theStateDefinitions):
	 tag(theTag)
{
	registerKeyword("capital", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt capitalInt(theStream);
		capital = capitalInt.getInt();
	});
	registerKeyword("civilized", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString civilizedString(theStream);
		if (civilizedString.getString() == "yes")
		{
			civilized = true;
		}
	});
	registerKeyword("revanchism", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble revanchismDouble(theStream);
		revanchism = revanchismDouble.getDouble();
	});
	registerKeyword("war_exhaustion", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble warExhaustionDouble(theStream);
		warExhaustion = warExhaustionDouble.getDouble();
	});
	registerKeyword("badboy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble badboyDouble(theStream);
		badboy = badboyDouble.getDouble();
	});
	registerKeyword("prestige", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble prestigeDouble(theStream);
		prestige = prestigeDouble.getDouble();
	});
	registerKeyword("government", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString governmentString(theStream);
		government = governmentString.getString();
	});
	registerKeyword("last_election", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString lastElectionString(theStream);
		lastElection = date(lastElectionString.getString());
	});
	registerKeyword("domain_region", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString regionString(theStream);
		domainName = regionString.getString();
		domainAdjective = domainName;
	});
	registerKeyword("human", [this](const std::string& unused, std::istream& theStream) {
		commonItems::ignoreItem(unused, theStream);
		human = true;
	});
	registerKeyword("primary_culture", [this, &theCultureGroups](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString cultureString(theStream);
		primaryCulture = stringutils::remQuotes(cultureString.getString());
		acceptedCultures.insert(primaryCulture);

		auto cultureGroupOption = theCultureGroups.getGroup(primaryCulture);
		if (cultureGroupOption)
		{
			primaryCultureGroup = *cultureGroupOption;
		}
		else
		{
			primaryCultureGroup.clear();
		}
	});
	registerKeyword("culture", [this](const std::string& unused, std::istream& theStream) {
		commonItems::stringList cultureString(theStream);
		for (auto culture: cultureString.getStrings())
		{
			if (culture.substr(0, 1) == "\"")
			{
				culture = culture.substr(1, culture.size() - 2);
			}
			acceptedCultures.insert(culture);
		}
	});
	registerKeyword("technology", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto openBrace = getNextTokenWithoutMatching(theStream);
		auto token = getNextTokenWithoutMatching(theStream);
		while (token != "}")
		{
			techs.insert(*token);
			commonItems::ignoreItem(*token, theStream);
			token = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword("active_inventions", [this, &theInventions](const std::string& unused, std::istream& theStream) {
		commonItems::intList inventionNums(theStream);
		for (auto inventionNum: inventionNums.getInts())
		{
			auto inventionName = theInventions.getInventionName(inventionNum);
			if (inventionName)
			{
				discoveredInventions.insert(*inventionName);
			}
		}
	});
	registerKeyword("active_party", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt partyNum(theStream);
		activePartyIDs.push_back(partyNum.getInt());
		if (rulingPartyID == 0)
		{
			rulingPartyID = partyNum.getInt();
		}
	});
	registerKeyword("ruling_party", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt partyNum(theStream);
		rulingPartyID = partyNum.getInt();
	});
	registerKeyword("upper_house", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto openBrace = getNextTokenWithoutMatching(theStream);
		auto token = getNextTokenWithoutMatching(theStream);
		while (token != "}")
		{
			commonItems::singleDouble ideologyAmount(theStream);
			upperHouseComposition.insert(make_pair(*token, ideologyAmount.getDouble()));
			token = getNextTokenWithoutMatching(theStream);
		}
	});
	registerRegex("[A-Z][A-Z0-9]{2}", [this](const std::string& countryTag, std::istream& theStream) {
		Relations* rel = new Relations(countryTag, theStream);
		relations.insert(make_pair(rel->getTag(), rel));
	});
	registerKeyword("army", [this](const std::string& type, std::istream& theStream) {
		Army army(type, theStream);
		armies.push_back(army);
	});
	registerKeyword("navy", [this](const std::string& type, std::istream& theStream) {
		Army navy(type, theStream);
		armies.push_back(navy);

		for (auto transportedArmy: navy.getTransportedArmies())
		{
			armies.push_back(transportedArmy);
		}
	});
	registerKeyword("leader", [this](const std::string& unused, std::istream& theStream) {
		Leader* leader = new Leader(theStream);
		leaders.push_back(leader);
	});
	registerKeyword("state", [this, &theStateDefinitions](const std::string& unused, std::istream& theStream) {
		State* newState = new State(theStream, tag, theStateDefinitions);
		states.push_back(newState);
	});
	registerKeyword("flags", [this](const std::string& unused, std::istream& theStream) {
		commonItems::assignments theFlags(theStream);
		for (auto flag: theFlags.getAssignments())
		{
			flags.insert(flag.first);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}


void Vic2::Country::eatCountry(Vic2::Country* target, bool debug)
{
	if (target->tag == tag)
	{
		return;
	}

	for (auto state: target->states)
	{
		states.push_back(state);
		state->setOwner(tag);
	}
	for (auto core: target->cores)
	{
		addCore(core);
		core->addCore(tag);
		core->removeCore(target->tag);
	}
	for (auto provinceItr: target->provinces)
	{
		addProvince(provinceItr);
		provinceItr.second->setOwner(tag);
	}
	techs.insert(target->techs.begin(), target->techs.end());
	discoveredInventions.insert(target->discoveredInventions.begin(), target->discoveredInventions.end());
	armies.insert(armies.end(), target->armies.begin(), target->armies.end());

	// coreless, landless countries will be cleaned up automatically
	target->provinces.clear();
	target->cores.clear();

	if (debug)
	{
		Log(LogLevel::Debug) << "Merged " << target->tag << " into " << tag;
	}
}


void Vic2::Country::putProvincesInStates()
{
	for (auto state: states)
	{
		for (auto provinceNum: state->getProvinceNumbers())
		{
			auto province = provinces.find(provinceNum);
			if (province == provinces.end())
			{
				Log(LogLevel::Warning) << "State owned by " << tag << " had province that " << tag << " did not";
				continue;
			}

			state->addProvince(province->second);
		}
	}
}


void Vic2::Country::determineEmployedWorkers()
{
	for (auto state: states)
	{
		state->determineEmployedWorkers();
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


void Vic2::Country::handleMissingCulture(const cultureGroups& theCultureGroups)
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

	for (auto province: provinces)
	{
		for (auto pop: province.second->getPops())
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

std::string Vic2::Country::getIdentifier() const
{
	std::string ret = getTag();
	auto name = getName("english");
	if (name)
	{
		ret += " (" + name.value() + ")";
	}
	return ret;
}

std::optional<std::string> Vic2::Country::getName(const std::string& language) const
{
	std::map<std::string, std::string>::const_iterator findIter = namesByLanguage.find(language);
	if (findIter != namesByLanguage.end())
	{
		return findIter->second;
	}
	else
	{
		return {};
	}
}


std::optional<std::string> Vic2::Country::getAdjective(const std::string& language) const
{
	std::map<std::string, std::string>::const_iterator findIter = adjectivesByLanguage.find(language);
	if (findIter != adjectivesByLanguage.end())
	{
		return findIter->second;
	}
	else
	{
		return {};
	}
}


double Vic2::Country::getUpperHousePercentage(const std::string& ideology) const
{
	std::map<std::string, double>::const_iterator itr = upperHouseComposition.find(ideology);
	if (itr == upperHouseComposition.end())
	{
		return 0.0;
	}

	return itr->second;
}


long Vic2::Country::getEmployedWorkers() const
{
	long employedWorkers = 0;
	for (auto state: states)
	{
		employedWorkers += state->getEmployedWorkers();
	}

	return employedWorkers;
}


std::optional<const Vic2::Party> Vic2::Country::getRulingParty(const std::vector<Vic2::Party>& allParties) const
{
	if ((rulingPartyID <= allParties.size()) && (rulingPartyID > 0))
	{
		return allParties.at(rulingPartyID - 1); // Subtract 1, because party ID starts from index of 1
	}
	else
	{
		return {};
	}
}


std::set<Vic2::Party> Vic2::Country::getActiveParties(const std::vector<Vic2::Party>& allParties) const
{
	std::set<Vic2::Party> activeParties;

	for (auto ID: activePartyIDs)
	{
		if (ID < allParties.size())
		{
			activeParties.insert(allParties[ID - 1]); // Subtract 1, because party ID starts from index of 1
		}
		else
		{
			Log(LogLevel::Warning) << "Party ID mismatch! Did some Vic2 country files not get read?";
		}
	}

	return activeParties;
}


bool Vic2::Country::hasCoreOnCapital() const
{
	for (auto core: cores)
	{
		if (core->getNumber() == capital)
		{
			return true;
		}
	}

	return false;
}

std::vector<std::string> Vic2::Country::getShipNames(const std::string& category) const
{
	auto foundShipNames = shipNames.find(category);
	if (foundShipNames == shipNames.end())
	{
		return std::vector<std::string>();
	}
	return foundShipNames->second;
}


double Vic2::Country::getAverageMilitancy() const
{
	int totalPopulation = 0;
	double totalMilitancy = 0.0;
	for (auto province: provinces)
	{
		auto pops = province.second->getPops();
		for (auto pop: pops)
		{
			int size = pop.getSize();
			totalMilitancy += pop.getMilitancy() * size;
			totalPopulation += size;
		}
	}

	return totalMilitancy / totalPopulation;
}


float Vic2::Country::getAverageIssueSupport(const std::string& issueName) const
{
	int totalPopulation = 0;
	float totalSupport = 0.0;
	for (auto province: provinces)
	{
		auto pops = province.second->getPops();
		for (auto pop: pops)
		{
			int size = pop.getSize();
			totalSupport += pop.getIssueSupport(issueName) * size;
			totalPopulation += size;
		}
	}

	return totalSupport / totalPopulation;
}


bool Vic2::operator==(const Vic2::Country& one, const Vic2::Country& other)
{
	return one.getTag() == other.getTag();
}