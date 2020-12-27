#include "CountryFactory.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "StringUtils.h"
#include "V2World/Culture/CultureGroupsFactory.h"
#include "V2World/Military/Leaders/TraitsFactory.h"
#include "V2World/Technology/InventionsFactory.h"
#include <cmath>
#include <sstream>



Vic2::Country::Factory::Factory(const Configuration& theConfiguration,
	 const StateDefinitions& theStateDefinitions,
	 std::shared_ptr<CultureGroups> theCultureGroups_):
	 theCultureGroups(std::move(theCultureGroups_)),
	 theInventions(Inventions::Factory{}.loadInventions(theConfiguration)),
	 leaderFactory(
		  std::make_unique<Leader::Factory>(std::move(*Traits::Factory{}.loadTraits(theConfiguration.getVic2Path())))),
	 stateFactory(std::make_unique<State::Factory>())
{
	registerKeyword("capital", [this](const std::string& unused, std::istream& theStream) {
		country->capital = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("civilized", [this](const std::string& unused, std::istream& theStream) {
		if (commonItems::singleString{theStream}.getString() == "yes")
		{
			country->civilized = true;
		}
	});
	registerKeyword("revanchism", [this](const std::string& unused, std::istream& theStream) {
		country->revanchism = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("war_exhaustion", [this](const std::string& unused, std::istream& theStream) {
		country->warExhaustion = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("badboy", [this](const std::string& unused, std::istream& theStream) {
		country->badBoy = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("government", [this](const std::string& unused, std::istream& theStream) {
		country->government = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("last_election", [this](const std::string& unused, std::istream& theStream) {
		country->lastElection = date(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("domain_region", [this](const std::string& unused, std::istream& theStream) {
		country->domainName = commonItems::singleString{theStream}.getString();
		country->domainAdjective = country->domainName;
	});
	registerKeyword("human", [this](const std::string& unused, std::istream& theStream) {
		if (commonItems::singleString{theStream}.getString() == "yes")
		{
			country->human = true;
		}
	});
	registerKeyword("primary_culture", [this](const std::string& unused, std::istream& theStream) {
		country->primaryCulture = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
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
		for (const auto& culture: commonItems::stringList{theStream}.getStrings())
		{
			country->acceptedCultures.insert(commonItems::remQuotes(culture));
		}
	});
	registerKeyword("technology", [this](const std::string& unused, std::istream& theStream) {
		for (const auto& technology: technologyFactory.importTechnologies(theStream))
		{
			country->technologiesAndInventions.insert(technology);
		}
	});
	registerKeyword("active_inventions", [this](const std::string& unused, std::istream& theStream) {
		for (auto inventionNum: commonItems::intList{theStream}.getInts())
		{
			if (auto inventionName = theInventions->getInventionName(inventionNum); inventionName)
			{
				country->technologiesAndInventions.insert(*inventionName);
			}
		}
	});
	registerKeyword("active_party", [this](const std::string& unused, std::istream& theStream) {
		const auto partyNum = commonItems::singleInt(theStream).getInt();
		country->activePartyIDs.push_back(partyNum);
		if (country->rulingPartyID == 0)
		{
			country->rulingPartyID = partyNum;
		}
	});
	registerKeyword("ruling_party", [this](const std::string& unused, std::istream& theStream) {
		country->rulingPartyID = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("upper_house", [this](const std::string& unused, std::istream& theStream) {
		for (const auto& [ideology, amountString]: commonItems::assignments{theStream}.getAssignments())
		{
			try
			{
				country->upperHouseComposition.insert(make_pair(ideology, stof(amountString)));
			}
			catch (...)
			{
				Log(LogLevel::Warning) << "Malformed input while importing upper house composition for " << country->tag;
			}
		}
	});
	registerRegex("[A-Z][A-Z0-9]{2}", [this](const std::string& countryTag, std::istream& theStream) {
		country->relations.insert(std::make_pair(countryTag, *relationsFactory.getRelations(theStream)));
	});
	registerKeyword("ai", [this](const std::string& unused, std::istream& theStream) {
		country->vic2AI = aiFactory.importAI(theStream);
	});
	registerKeyword("army", [this](const std::string& unused, std::istream& theStream) {
		country->armies.push_back(*armyFactory.getArmy(country->tag, theStream));
	});
	registerKeyword("navy", [this](const std::string& unused, std::istream& theStream) {
		const auto navy = armyFactory.getArmy(country->tag, theStream);
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
		country->states.push_back(*stateFactory->getState(theStream, country->tag, theStateDefinitions));
	});
	registerKeyword("flags", [this](const std::string& unused, std::istream& theStream) {
		for (const auto& [flag, unused]: commonItems::assignments{theStream}.getAssignments())
		{
			country->flags.insert(flag);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Country> Vic2::Country::Factory::createCountry(const std::string& theTag,
	 std::istream& theStream,
	 const CommonCountryData& commonCountryData,
	 const std::vector<Party>& allParties,
	 const StateLanguageCategories& stateLanguageCategories)
{
	country = std::make_unique<Country>();
	country->tag = theTag;
	country->color = commonCountryData.getColor();
	country->shipNames = commonCountryData.getUnitNames();

	parseStream(theStream);
	setParties(allParties);
	limitCommanders();

	if (!country->vic2AI)
	{
		country->vic2AI = std::make_unique<AI>();
	}

	setStateLanguageCategories(stateLanguageCategories);

	return std::move(country);
}


void Vic2::Country::Factory::setParties(const std::vector<Party>& allParties)
{
	if (country->tag == "REB")
	{
		return;
	}
	for (auto ID: country->activePartyIDs)
	{
		if (ID <= allParties.size())
		{
			country->activeParties.insert(allParties.at(ID - 1)); // Subtract 1, because party ID starts from index of 1
		}
		else
		{
			Log(LogLevel::Warning) << "Party ID mismatch! Did some Vic2 country files not get read?";
		}
	}

	if (country->rulingPartyID == 0)
	{
		throw std::runtime_error(country->tag + " had no ruling party. The save needs manual repair.");
	}
	if (country->rulingPartyID > allParties.size())
	{
		throw std::runtime_error(
			 "Could not find the ruling party for " + country->tag + ". " + "Most likely a mod was not included.\n" +
			 "Double-check your settings, and remember to include EU4 to Vic2 mods. See the FAQ for more information.");
	}
	country->rulingParty =
		 allParties.at(country->rulingPartyID - 1); // Subtract 1, because party ID starts from index of 1
}


void Vic2::Country::Factory::limitCommanders()
{
	std::vector<Leader> generals;
	std::copy_if(country->leaders.begin(),
		 country->leaders.end(),
		 std::back_inserter(generals),
		 [](const Leader& leader) {
			 return leader.getType() == "land";
		 });
	std::sort(generals.begin(), generals.end(), [](Leader& a, Leader& b) {
		return a.getPrestige() > b.getPrestige();
	});
	const auto desiredGenerals = static_cast<int>(std::ceil(static_cast<float>(generals.size()) / 20.0F));
	generals.erase(generals.begin() + desiredGenerals, generals.end());

	std::vector<Leader> admirals;
	std::copy_if(country->leaders.begin(),
		 country->leaders.end(),
		 std::back_inserter(admirals),
		 [](const Leader& leader) {
			 return leader.getType() == "sea";
		 });
	std::sort(admirals.begin(), admirals.end(), [](Leader& a, Leader& b) {
		return a.getPrestige() > b.getPrestige();
	});
	const auto desiredAdmirals = static_cast<int>(std::ceil(static_cast<float>(admirals.size()) / 20.0F));
	admirals.erase(admirals.begin() + desiredAdmirals, admirals.end());

	country->leaders.clear();
	std::move(generals.begin(), generals.end(), std::back_inserter(country->leaders));
	std::move(admirals.begin(), admirals.end(), std::back_inserter(country->leaders));
}


void Vic2::Country::Factory::setStateLanguageCategories(const StateLanguageCategories& stateLanguageCategories)
{
	for (auto& state: country->states)
	{
		const auto category = stateLanguageCategories.getStateCategory(state.getStateID());
		if (category)
		{
			state.setLanguageCategory(*category);
		}
		else
		{
			Log(LogLevel::Warning) << state.getStateID() << " was not in any language category.";
		}
	}
}