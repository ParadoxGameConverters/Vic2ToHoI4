#include "CountryFactory.h"
#include "ParserHelpers.h"
#include "StringUtils.h"
#include "V2World/Culture/CultureGroupsFactory.h"
#include "V2World/Military/Leaders/TraitsFactory.h"
#include "V2World/Technology/InventionsFactory.h"
#include <sstream>



Vic2::Country::Factory::Factory(const Configuration& theConfiguration,
	 const StateDefinitions& theStateDefinitions,
	 std::shared_ptr<CultureGroups> theCultureGroups_):
	 theCultureGroups(std::move(theCultureGroups_))
{
	theInventions = Inventions::Factory{}.loadInventions(theConfiguration);
	Traits traits = *Traits::Factory{}.loadTraits(theConfiguration.getVic2Path());
	leaderFactory = std::make_unique<Leader::Factory>(std::move(traits));
	stateFactory = std::make_unique<State::Factory>();

	registerKeyword("capital", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt capitalInt(theStream);
		country->capital = capitalInt.getInt();
	});
	registerKeyword("civilized", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString civilizedString(theStream);
		if (civilizedString.getString() == "yes")
		{
			country->civilized = true;
		}
	});
	registerKeyword("revanchism", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble revanchismDouble(theStream);
		country->revanchism = revanchismDouble.getDouble();
	});
	registerKeyword("war_exhaustion", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble warExhaustionDouble(theStream);
		country->warExhaustion = warExhaustionDouble.getDouble();
	});
	registerKeyword("badboy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble badboyDouble(theStream);
		country->badBoy = badboyDouble.getDouble();
	});
	registerKeyword("government", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString governmentString(theStream);
		country->government = governmentString.getString();
	});
	registerKeyword("last_election", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString lastElectionString(theStream);
		country->lastElection = date(lastElectionString.getString());
	});
	registerKeyword("domain_region", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString regionString(theStream);
		country->domainName = regionString.getString();
		country->domainAdjective = country->domainName;
	});
	registerKeyword("human", [this](const std::string& unused, std::istream& theStream) {
		commonItems::ignoreItem(unused, theStream);
		country->human = true;
	});
	registerKeyword("primary_culture", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString cultureString(theStream);
		country->primaryCulture = commonItems::remQuotes(cultureString.getString());
		country->acceptedCultures.insert(country->primaryCulture);

		auto cultureGroupOption = theCultureGroups->getGroup(country->primaryCulture);
		if (cultureGroupOption)
		{
			country->primaryCultureGroup = *cultureGroupOption;
		}
		else
		{
			country->primaryCultureGroup.clear();
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
			country->acceptedCultures.insert(culture);
		}
	});
	registerKeyword("technology", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto openBrace = getNextTokenWithoutMatching(theStream);
		auto token = getNextTokenWithoutMatching(theStream);
		while (token != "}")
		{
			country->technologiesAndInventions.insert(*token);
			commonItems::ignoreItem(*token, theStream);
			token = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword("active_inventions", [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList inventionNums(theStream);
		for (auto inventionNum: inventionNums.getInts())
		{
			auto inventionName = theInventions->getInventionName(inventionNum);
			if (inventionName)
			{
				country->technologiesAndInventions.insert(*inventionName);
			}
		}
	});
	registerKeyword("active_party", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt partyNum(theStream);
		country->activePartyIDs.push_back(partyNum.getInt());
		if (country->rulingPartyID == 0)
		{
			country->rulingPartyID = partyNum.getInt();
		}
	});
	registerKeyword("ruling_party", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt partyNum(theStream);
		country->rulingPartyID = partyNum.getInt();
	});
	registerKeyword("upper_house", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto openBrace = getNextTokenWithoutMatching(theStream);
		auto token = getNextTokenWithoutMatching(theStream);
		while (token != "}")
		{
			commonItems::singleDouble ideologyAmount(theStream);
			country->upperHouseComposition.insert(make_pair(*token, ideologyAmount.getDouble()));
			token = getNextTokenWithoutMatching(theStream);
		}
	});
	registerRegex("[A-Z][A-Z0-9]{2}", [this](const std::string& countryTag, std::istream& theStream) {
		country->relations.insert(std::make_pair(countryTag, *relationsFactory.getRelations(theStream)));
	});
	registerKeyword("ai", [this](const std::string& unused, std::istream& theStream) {
		country->vic2AI = std::make_unique<Vic2AI>(theStream);
	});
	registerKeyword("army", [this](const std::string& unused, std::istream& theStream) {
		country->armies.push_back(*armyFactory.getArmy(theStream));
	});
	registerKeyword("navy", [this](const std::string& unused, std::istream& theStream) {
		auto navy = armyFactory.getArmy(theStream);
		for (auto& transportedArmy: navy->getTransportedArmies())
		{
			country->armies.push_back(transportedArmy);
		}
		country->armies.push_back(*navy);
	});
	registerKeyword("leader", [this](const std::string& unused, std::istream& theStream) {
		country->leaders.push_back(*leaderFactory->getLeader(theStream));
	});
	registerKeyword("state", [this, &theStateDefinitions](const std::string& unused, std::istream& theStream) {
		auto newState = stateFactory->getState(theStream, country->tag, theStateDefinitions);
		country->states.push_back(*newState);
	});
	registerKeyword("flags", [this](const std::string& unused, std::istream& theStream) {
		commonItems::assignments theFlags(theStream);
		for (auto flag: theFlags.getAssignments())
		{
			country->flags.insert(flag.first);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Country> Vic2::Country::Factory::createCountry(const std::string& theTag,
	 std::istream& theStream,
	 const CommonCountryData& commonCountryData,
	 const std::vector<Party>& allParties)
{
	country = std::make_unique<Country>();
	country->tag = theTag;
	country->color = commonCountryData.getColor();
	country->shipNames = commonCountryData.getUnitNames();

	parseStream(theStream);
	country->setParties(allParties);

	if (!country->vic2AI)
	{
		std::stringstream input;
		country->vic2AI = std::make_unique<Vic2AI>(input);
	}

	return std::move(country);
}