#include "HoI4Country.h"
#include "Advisor.h"
#include "HoI4World.h"
#include "Log.h"
#include "HoI4Leader.h"
#include "HoI4Localisation.h"
#include "HoI4War.h"
#include "Names.h"
#include "MilitaryMappings/MilitaryMappings.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/GovernmentMapper.h"
#include "../Mappers/GraphicsMapper.h"
#include "../Mappers/Provinces/ProvinceMapper.h"
#include "../Mappers/TechMapper.h"
#include "../V2World/Country.h"
#include "../V2World/Relations.h"
#include "../V2World/Party.h"
#include "../V2World/World.h"
#include "../Mappers/Provinces/ProvinceMapper.h"
#include "OSCompatibilityLayer.h"
#include <algorithm>



HoI4::Country::Country(
	std::string tag,
	const Vic2::Country* srcCountry,
	namesMapper& theNames,
	const graphicsMapper& theGraphics,
	const CountryMapper& countryMap,
	const mappers::FlagsToIdeasMapper& flagsToIdeasMapper
): tag(std::move(tag)), sourceCountry(*srcCountry)
{
	determineFilename();

	human = sourceCountry.isHuman();
	color = sourceCountry.getColor();
	civilized = sourceCountry.isCivilized();
	threat = sourceCountry.getBadBoy() / 10.0;
	auto possibleGraphicalCulture = theGraphics.getGraphicalCulture(sourceCountry.getPrimaryCultureGroup());
	if (possibleGraphicalCulture)
	{
		graphicalCulture = *possibleGraphicalCulture;
	}
	auto possibleGraphicalCulture2d = theGraphics.get2dGraphicalCulture(sourceCountry.getPrimaryCultureGroup());
	if (possibleGraphicalCulture2d)
	{
		graphicalCulture2d = *possibleGraphicalCulture2d;
	}
	lastElection = sourceCountry.getLastElection();
	initIdeas(theNames);

	stability = 60;
	warSupport = 60;

	if (!sourceCountry.getProvinces().empty())
	{
		auto warAttitude = sourceCountry.getAverageIssueSupport("jingoism");
		warAttitude += sourceCountry.getAverageIssueSupport("pro_military") / 2;
		warAttitude -= sourceCountry.getAverageIssueSupport("anti_military") / 2;
		warAttitude -= sourceCountry.getAverageIssueSupport("pacifism");
		warSupport += static_cast<int>(
			(warAttitude * 0.375)
			+ (sourceCountry.getRevanchism() / 5.0)
			- (sourceCountry.getWarExhaustion() / 2.5)
		);
		if (warSupport < 15)
		{
			warSupport = 15;
		}
	}

	for (const auto& flag: sourceCountry.getFlags())
	{
		auto possibleIdea = flagsToIdeasMapper.getIdea(flag);
		if (possibleIdea)
		{
			ideas.insert(*possibleIdea);
		}
	}

	convertLeaders(theGraphics);
	convertRelations(countryMap);
	convertWars(*srcCountry, countryMap);

	theArmy.addSourceArmies(sourceCountry.getArmies());
}


void HoI4::Country::determineFilename()
{
	auto possibleFilename = sourceCountry.getName("english");
	if (possibleFilename)
	{
		filename = Utils::convertWin1252ToUTF8(*possibleFilename);
		auto pipe = filename.find_first_of('|');
		while (pipe != string::npos)
		{
			filename.replace(pipe, 1, "");
			pipe = filename.find_first_of('|');
		}
		auto greater = filename.find_first_of('>');
		while (greater != string::npos)
		{
			filename.replace(greater, 1, "");
			greater = filename.find_first_of('>');
		}
		auto lesser = filename.find_first_of('<');
		while (lesser != string::npos)
		{
			filename.replace(lesser, 1, "");
			lesser = filename.find_first_of('>');
		}

		commonCountryFile = filename + ".txt";
		filename = tag + " - " + filename + ".txt";
	}
	else
	{
		filename = tag + ".txt";
		commonCountryFile = tag + ".txt";
	}
}


void HoI4::Country::convertGovernment(const Vic2::World& sourceWorld, const governmentMapper& governmentMap)
{
	auto possibleRulingParty = sourceCountry.getRulingParty(sourceWorld.getParties());
	if (!possibleRulingParty)
	{
		throw std::runtime_error("Could not find the ruling party for " + sourceCountry.getTag() + ". "
			+ "Most likely a mod was not included.\n"
			+ "Double-check your settings, and remember to include EU4 to Vic2 mods. See the FAQ for more information."
		);
	}

	rulingParty = *possibleRulingParty;
	auto sourceTag = sourceCountry.getTag();
	auto sourceGovernment = sourceCountry.getGovernment();
	auto rulingIdeology = rulingParty.getIdeology();
	governmentIdeology = governmentMap.getIdeologyForCountry(
		sourceTag,
		sourceGovernment,
		rulingIdeology
	);
	leaderIdeology = governmentMap.getLeaderIdeologyForCountry(
		sourceTag,
		sourceGovernment,
		rulingIdeology
	);
	parties = sourceCountry.getActiveParties(sourceWorld.getParties());
	for (const auto& party: parties)
	{
		auto partyName = party.getName();
		auto trimmedName = partyName.substr(4, partyName.size());
		HoI4Localisation::addPoliticalPartyLocalisation(partyName, tag + "_" + trimmedName + "_party");
	}

	convertLaws();
}


void HoI4::Country::convertParties(const set<string>& majorIdeologies, const governmentMapper& governmentMap)
{
	for (const auto& HoI4Ideology: majorIdeologies)
	{
		for (const auto& party: parties)
		{
			if (
				HoI4Ideology == governmentMap.getSupportedIdeology(
					governmentIdeology,
					party.getIdeology(),
					majorIdeologies
				)
			)
			{
				HoI4Localisation::addPoliticalPartyLocalisation(
					party.getName(), tag + "_" + HoI4Ideology + "_party"
				);
			}
		}
	}
	HoI4Localisation::addPoliticalPartyLocalisation(
		rulingParty.getName(), tag + "_" + governmentIdeology + "_party"
	);
}


void HoI4::Country::initIdeas(namesMapper& theNames) const
{
	HoI4Localisation::addIdeaLocalisation(
		tag + "_tank_manufacturer", theNames.takeCarCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_motorized_equipment_manufacturer",
		theNames.takeCarCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_infantry_equipment_manufacturer",
		theNames.takeWeaponCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_artillery_manufacturer", theNames.takeWeaponCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_light_aircraft_manufacturer",
		theNames.takeAircraftCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_medium_aircraft_manufacturer",
		theNames.takeAircraftCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_heavy_aircraft_manufacturer",
		theNames.takeAircraftCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_naval_aircraft_manufacturer",
		theNames.takeAircraftCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_naval_manufacturer", theNames.takeNavalCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_industrial_concern", theNames.takeIndustryCompanyName(sourceCountry.getPrimaryCulture())
	);
	HoI4Localisation::addIdeaLocalisation(
		tag + "_electronics_concern", theNames.takeElectronicCompanyName(sourceCountry.getPrimaryCulture())
	);
}


void HoI4::Country::convertLaws()
{
	// mobilization laws are based on the ruling party's war policy
	if (rulingParty.getWarPolicy() == "jingoism")
	{
		mobilizationLaw = "limited_conscription";
	}
	else if (rulingParty.getWarPolicy() == "pacifism")
	{
		mobilizationLaw = "disarmed_nation";
	}

	// if at war, more economic mobilization
	if (sourceCountry.isAtWar())
	{
		economicLaw = "low_economic_mobilisation";
	}

	// some ideologies have non-default laws
	if (governmentIdeology == "fascism")
	{
		economicLaw = "partial_economic_mobilisation";
		tradeLaw = "limited_exports";
	}
	else if (governmentIdeology == "radical")
	{
		tradeLaw = "free_trade";
	}
}


void HoI4::Country::convertLeaders(const graphicsMapper& theGraphics)
{
	auto srcLeaders = sourceCountry.getLeaders();
	for (auto srcLeader: srcLeaders)
	{
		if (srcLeader->getType() == "land")
		{
			General newLeader(srcLeader, theGraphics.getGeneralPortrait(graphicalCulture));
			generals.push_back(newLeader);
		}
		else if (srcLeader->getType() == "sea")
		{
			Admiral newLeader(srcLeader, theGraphics.getGeneralPortrait(graphicalCulture));
			admirals.push_back(newLeader);
		}
	}

	theConfiguration.setLeaderIDForNextCountry();
}


void HoI4::Country::convertRelations(const CountryMapper& countryMap)
{
	auto srcRelations = sourceCountry.getRelations();
	for (const auto& srcRelation: srcRelations)
	{
		auto HoI4Tag = countryMap.getHoI4Tag(srcRelation.second->getTag());
		if (HoI4Tag)
		{
			HoI4Relations newRelation(*HoI4Tag, srcRelation.second);
			relations.insert(make_pair(*HoI4Tag, std::move(newRelation)));
		}
	}
}


void HoI4::Country::convertWars(const Vic2::Country& sourceCountry, const CountryMapper& countryMap)
{
	for (const auto& sourceWar: sourceCountry.getWars())
	{
		War theWar(sourceWar, countryMap);
		wars.push_back(theWar);
	}
}


void HoI4::Country::determineCapitalFromVic2(
	const provinceMapper& theProvinceMapper,
	const std::map<int, int>& provinceToStateIDMap,
	const map<int, State>& allStates
)
{
	bool success = attemptToPutCapitalInPreferredNonWastelandOwned(theProvinceMapper, provinceToStateIDMap, allStates);
	if (!success)
	{
		success = attemptToPutCapitalInNonWastelandOwned(allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInPreferredWastelandOwned(theProvinceMapper, provinceToStateIDMap, allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInAnyOwned(allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInPreferredNonWastelandCored(theProvinceMapper, provinceToStateIDMap, allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInAnyNonWastelandCored(allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInPreferredWastelandCored(theProvinceMapper, provinceToStateIDMap, allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInAnyCored(allStates);
	}
	if (!success)
	{
		LOG(LogLevel::Warning) << "Could not properly set capital for " << tag;
	}
}


bool HoI4::Country::attemptToPutCapitalInPreferredNonWastelandOwned(
	const provinceMapper& theProvinceMapper,
	const map<int, int>& provinceToStateIDMap,
	const map<int, State>& allStates
)
{
	const auto oldCapital = sourceCountry.getCapital();
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (
			const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			capitalStateMapping != provinceToStateIDMap.end()
			)
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if ((state.getOwner() == tag) && !state.isImpassable())
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = (*mapping)[0];
				return true;
			}
		}
	}

	return false;
}



bool HoI4::Country::attemptToPutCapitalInNonWastelandOwned(const map<int, State>& allStates)
{
	for (auto ownedStateNum : states)
	{
		if (auto state = allStates.find(ownedStateNum); state != allStates.end())
		{
			if ((state->second.getOwner() == tag) && !state->second.isImpassable())
			{
				capitalState = ownedStateNum;
				capitalProvince = *state->second.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInPreferredWastelandOwned(
	const provinceMapper& theProvinceMapper,
	const std::map<int, int>& provinceToStateIDMap,
	const map<int, State>& allStates
)
{
	const auto oldCapital = sourceCountry.getCapital();
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (
			const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			capitalStateMapping != provinceToStateIDMap.end()
			)
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if (state.getOwner() == tag)
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = (*mapping)[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyOwned(const map<int, State>& allStates)
{
	for (auto ownedStateNum : states)
	{
		if (auto state = allStates.find(ownedStateNum); state != allStates.end())
		{
			if (state->second.getOwner() == tag)
			{
				capitalState = ownedStateNum;
				capitalProvince = *state->second.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInPreferredNonWastelandCored(
	const provinceMapper& theProvinceMapper,
	const std::map<int, int>& provinceToStateIDMap,
	const map<int, State>& allStates
)
{
	const auto oldCapital = sourceCountry.getCapital();
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (
			const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			capitalStateMapping != provinceToStateIDMap.end()
			)
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if ((state.getCores().count(tag) > 0) && !state.isImpassable())
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = (*mapping)[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyNonWastelandCored(const map<int, State>& allStates)
{
	for (auto ownedStateNum: states)
	{
		if (auto state = allStates.find(ownedStateNum); state != allStates.end())
		{
			if ((state->second.getCores().count(tag) > 0) && !state->second.isImpassable())
			{
				capitalState = ownedStateNum;
				capitalProvince = *state->second.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInPreferredWastelandCored(
	const provinceMapper& theProvinceMapper,
	const std::map<int, int>& provinceToStateIDMap,
	const map<int, State>& allStates
)
{
	const auto oldCapital = sourceCountry.getCapital();
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (
			const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			capitalStateMapping != provinceToStateIDMap.end()
			)
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if (state.getCores().count(tag) > 0)
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = (*mapping)[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyCored(const map<int, State>& allStates)
{
	for (auto ownedStateNum: states)
	{
		if (auto state = allStates.find(ownedStateNum); state != allStates.end())
		{
			if (state->second.getCores().count(tag) > 0)
			{
				capitalState = ownedStateNum;
				capitalProvince = *state->second.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


void HoI4::Country::convertTechnology(const mappers::techMapper& theTechMapper)
{
	auto oldTechs = sourceCountry.getTechs();
	auto oldInventions = sourceCountry.getInventions();
	theTechnologies = HoI4::technologies(theTechMapper, oldTechs, oldInventions);
}


void HoI4::Country::setGovernmentToExistingIdeology(
	const set<string>& majorIdeologies,
	const map<string, HoI4Ideology*>& ideologies,
	const governmentMapper& governmentMap
) {
	governmentIdeology = governmentMap.getExistingIdeologyForCountry(
		sourceCountry,
		rulingParty.getIdeology(),
		majorIdeologies,
		ideologies
	);
	leaderIdeology = governmentMap.getExistingLeaderIdeologyForCountry(
		sourceCountry,
		rulingParty.getIdeology(),
		majorIdeologies,
		ideologies
	);
}


void HoI4::Country::convertIdeologySupport(
	const std::set<std::string>& majorIdeologies,
	const governmentMapper& governmentMap
) {
	ideologySupport.clear();

	for (const auto& upperHouseIdeology: sourceCountry.getUpperHouseComposition())
	{
		auto ideology = governmentMap.getSupportedIdeology(
			governmentIdeology,
			upperHouseIdeology.first,
			majorIdeologies
		);
		auto supportItr = ideologySupport.find(ideology);
		if (supportItr == ideologySupport.end())
		{
			ideologySupport.insert(make_pair(ideology, 0));
			supportItr = ideologySupport.find(ideology);
		}
		supportItr->second += static_cast<int>(upperHouseIdeology.second * 100);
	}

	auto remainingSupport = 100;
	for (const auto& ideology: ideologySupport)
	{
		remainingSupport -= ideology.second;
	}
	if (remainingSupport > 0)
	{
		auto supportItr = ideologySupport.find("neutrality");
		if (supportItr == ideologySupport.end())
		{
			ideologySupport.insert(make_pair("neutrality", 0));
			supportItr = ideologySupport.find("neutrality");
		}
		supportItr->second += remainingSupport;
	}
}


void HoI4::Country::determineShipVariants(const std::vector<shipVariant>& possibleVariants)
{
	theShipVariants = std::make_unique<shipVariants>(possibleVariants, *theTechnologies, tag);
}


void HoI4::Country::convertNavies(
	const UnitMappings& unitMap,
	const MtgUnitMappings& mtgUnitMap,
	const coastalProvinces& theCoastalProvinces,
	const std::map<int, int>& provinceToStateIDMap,
	const std::map<int, State>& allStates)
{
	auto backupNavalLocation = 0;
	for (const auto& state: allStates)
	{
		if (state.second.getOwner() == tag)
		{
			auto mainNavalLocation = state.second.getMainNavalLocation();
			if (mainNavalLocation)
			{
				// Mapped ships will be placed in a single large fleet
				backupNavalLocation = *mainNavalLocation;
			}
		}
	}

	theNavies = std::make_unique<Navies>(
		sourceCountry.getArmies(),
		backupNavalLocation,
		unitMap,
		mtgUnitMap,
		*theShipVariants,
		theCoastalProvinces,
		provinceToStateIDMap,
		allStates,
		tag);
}


void HoI4::Country::convertConvoys(const UnitMappings& unitMap)
{
	for (auto army : sourceCountry.getArmies())
	{
		for (auto regiment : army->getRegiments())
		{
			if (auto type = regiment->getType(); unitMap.hasMatchingType(type))
			{
				if (auto unitInfo = unitMap.getMatchingUnitInfo(type); unitInfo.getCategory() == "convoy")
				{
					// Convoys get placed in national stockpile
					convoys = convoys + unitInfo.getSize();
				}
			}
			else
			{
				LOG(LogLevel::Warning) << "Unknown unit type: " << type;
			}
		}
	}
}


void HoI4::Country::convertAirForce(const UnitMappings& unitMap)
{
	static std::map<std::string, vector<std::string>> backups = {
		{"fighter_equipment_0", {"tac_bomber_equipment_0"}}
	};
	for (auto army : sourceCountry.getArmies())
	{
		for (auto regiment : army->getRegiments())
		{
			if (auto type = regiment->getType(); unitMap.hasMatchingType(type))
			{
				auto unitInfo = unitMap.getMatchingUnitInfo(type);
				if (unitInfo.getCategory() != "air")
				{
					continue;
				}

				// Air units get placed in national stockpile.
				auto equip = unitInfo.getEquipment();
				unsigned int amount = unitInfo.getSize();
				const auto& backup = backups.find(equip);
				if (backup != backups.end())
				{
					amount /= (1 + backup->second.size());
					for (const auto& b : backup->second)
					{
						equipmentStockpile[b] += amount;
					}
				}
				equipmentStockpile[equip] += amount;
			}
			else
			{
				LOG(LogLevel::Warning) << "Unknown unit type: " << type;
			}
		}
	}
}


void HoI4::Country::convertArmies(const militaryMappings& theMilitaryMappings)
{
	if (capitalProvince)
	{
		theArmy.convertArmies(theMilitaryMappings, *capitalProvince, theConfiguration.getForceMultiplier());
	}
	else
	{
		theArmy.convertArmies(theMilitaryMappings, 0, theConfiguration.getForceMultiplier());
	}
}


void HoI4::Country::addState(const State& state)
{
	states.insert(state.getID());

	for (const auto province: state.getProvinces())
	{
		provinces.insert(province);
	}
}


std::optional<HoI4Relations> HoI4::Country::getRelations(const std::string& withWhom) const
{
	if (const auto theRelations = relations.find(withWhom); theRelations != relations.end())
	{
		return theRelations->second;
	}
	else
	{
		return {};
	}
}


void HoI4::Country::calculateIndustry(const std::map<int, State>& allStates)
{
	for (const auto& state: allStates)
	{
		if (state.second.getOwner() == tag)
		{
			civilianFactories += state.second.getCivFactories();
			militaryFactories += state.second.getMilFactories();
			dockyards += state.second.getDockyards();
		}
	}
}


void HoI4::Country::addGenericFocusTree(const std::set<string>& majorIdeologies)
{
	if (!nationalFocus)
	{
		HoI4FocusTree genericNationalFocus(*this);
		genericNationalFocus.addGenericFocusTree(majorIdeologies);
		nationalFocus = genericNationalFocus.makeCustomizedCopy(*this);
	}
}


void HoI4::Country::adjustResearchFocuses() const
{
	if (greatPower && nationalFocus)
	{
		nationalFocus->removeFocus("extra_tech_slot_2" + tag);
	}
}


double HoI4::Country::getStrengthOverTime(const double& years) const
{
	return getMilitaryStrength() + getEconomicStrength(years);
}


double HoI4::Country::getMilitaryStrength()
{
	return 0.0;
}


double HoI4::Country::getEconomicStrength(const double& years) const
{
	constexpr auto militaryFactoriesPerYear = 0.469f;
	constexpr auto factoriesUsedForConsumerGoods = 0.5f;
	constexpr auto daysPerYear = 365;

	const auto militarySectorStrength = militaryFactories * 3 * daysPerYear * years;
	const auto civilianSectorStrength =
		civilianFactories
		* militaryFactoriesPerYear
		* factoriesUsedForConsumerGoods
		* factoriesUsedForConsumerGoods
		* 3
		* daysPerYear
		* years
		* years;

	return militarySectorStrength + civilianSectorStrength;
}


bool HoI4::Country::areElectionsAllowed() const
{
	return
		(governmentIdeology == "democratic") ||
		(
			(governmentIdeology == "neutrality") &&
			(
				(leaderIdeology == "conservatism_neutral") ||
				(leaderIdeology == "liberalism_neutral") ||
				(leaderIdeology == "socialism_neutral")
			)
		);
}


std::optional<HoI4Faction> HoI4::Country::getFaction() const
{
	if (faction)
	{
		return std::make_optional(*faction);
	}
	else
	{
		return nullopt;
	}
}


std::optional<HoI4FocusTree> HoI4::Country::getNationalFocus() const
{
	if (nationalFocus)
	{
		return std::make_optional(*nationalFocus);
	}
	else
	{
		return nullopt;
	}
}