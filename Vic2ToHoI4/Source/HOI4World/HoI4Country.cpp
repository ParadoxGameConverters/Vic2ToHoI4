#include "HoI4Country.h"
#include "Diplomacy/HoI4War.h"
#include "HoI4Localisation.h"
#include "HoI4World.h"
#include "Leaders/CountryLeaderFactory.h"
#include "Log.h"
#include "Mappers/CountryMapping.h"
#include "Mappers/GovernmentMapper.h"
#include "Mappers/GraphicsMapper.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Technology/TechMapper.h"
#include "MilitaryMappings/MilitaryMappings.h"
#include "Names/Names.h"
#include "OSCompatibilityLayer.h"
#include "V2World/Ai/AI.h"
#include "V2World/Ai/AIStrategy.h"
#include "V2World/Countries/Country.h"
#include "V2World/Politics/Party.h"
#include "V2World/World/World.h"
#include <algorithm>



HoI4::Country::Country(std::string tag,
	 const Vic2::Country& sourceCountry,
	 Names& names,
	 graphicsMapper& theGraphics,
	 const CountryMapper& countryMap,
	 const mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
	 Localisation& hoi4Localisations):
	 tag(std::move(tag)),
	 name(sourceCountry.getName("english")), adjective(sourceCountry.getAdjective("english")),
	 oldTag(sourceCountry.getTag()), human(human = sourceCountry.isHuman()), threat(sourceCountry.getBadBoy() / 10.0),
	 oldCapital(sourceCountry.getCapital()), primaryCulture(sourceCountry.getPrimaryCulture()),
	 civilized(sourceCountry.isCivilized()), primaryCultureGroup(sourceCountry.getPrimaryCultureGroup()),
	 rulingParty(sourceCountry.getRulingParty()), parties(sourceCountry.getActiveParties()),
	 oldGovernment(sourceCountry.getGovernment()), upperHouseComposition(sourceCountry.getUpperHouseComposition()),
	 lastElection(sourceCountry.getLastElection())
{
	determineFilename();

	const auto& sourceColor = sourceCountry.getColor();
	if (sourceColor)
	{
		color = *sourceColor;
	}

	auto possibleGraphicalCulture = theGraphics.getGraphicalCulture(primaryCultureGroup);
	if (possibleGraphicalCulture)
	{
		graphicalCulture = *possibleGraphicalCulture;
	}
	auto possibleGraphicalCulture2d = theGraphics.get2dGraphicalCulture(primaryCultureGroup);
	if (possibleGraphicalCulture2d)
	{
		graphicalCulture2d = *possibleGraphicalCulture2d;
	}
	communistAdvisorPortrait = theGraphics.getIdeologyMinisterPortrait(primaryCultureGroup, "communism");
	democraticAdvisorPortrait = theGraphics.getIdeologyMinisterPortrait(primaryCultureGroup, "democratic");
	neutralityAdvisorPortrait = theGraphics.getIdeologyMinisterPortrait(primaryCultureGroup, "neutrality");
	absolutistAdvisorPortrait = theGraphics.getIdeologyMinisterPortrait(primaryCultureGroup, "absolutist");
	radicalAdvisorPortrait = theGraphics.getIdeologyMinisterPortrait(primaryCultureGroup, "radical");
	fascistAdvisorPortrait = theGraphics.getIdeologyMinisterPortrait(primaryCultureGroup, "fascism");

	initIdeas(names, hoi4Localisations);

	stability = 60;
	warSupport = 60;

	if (sourceCountry.hasLand())
	{
		auto warAttitude = sourceCountry.getAverageIssueSupport("jingoism");
		warAttitude += sourceCountry.getAverageIssueSupport("pro_military") / 2;
		warAttitude -= sourceCountry.getAverageIssueSupport("anti_military") / 2;
		warAttitude -= sourceCountry.getAverageIssueSupport("pacifism");
		warSupport += static_cast<int>(
			 (warAttitude * 0.375) + (sourceCountry.getRevanchism() / 5.0) - (sourceCountry.getWarExhaustion() / 2.5));
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

	oldTechnologiesAndInventions = sourceCountry.getTechnologiesAndInventions();

	convertLeaders(theGraphics, sourceCountry);
	convertRelations(countryMap, sourceCountry);
	atWar = sourceCountry.isAtWar();
	convertWars(sourceCountry, countryMap);

	employedWorkers = sourceCountry.getEmployedWorkers();

	oldArmies = sourceCountry.getArmies();
	theArmy.addSourceArmies(oldArmies);
	shipNames = sourceCountry.getAllShipNames();
}


void HoI4::Country::determineFilename()
{
	if (name)
	{
		filename = commonItems::convertWin1252ToUTF8(*name);
		auto pipe = filename.find_first_of('|');
		while (pipe != std::string::npos)
		{
			filename.replace(pipe, 1, "");
			pipe = filename.find_first_of('|');
		}
		auto greater = filename.find_first_of('>');
		while (greater != std::string::npos)
		{
			filename.replace(greater, 1, "");
			greater = filename.find_first_of('>');
		}
		auto lesser = filename.find_first_of('<');
		while (lesser != std::string::npos)
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


void HoI4::Country::convertGovernment(const Vic2::World& sourceWorld,
	 const governmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 bool debug)
{
	if (rulingParty == std::nullopt)
	{
		return;
	}
	if (oldTag == "AAA")
	{
		return;
	}
	if (oldTag == "UCV")
	{
		return;
	}

	auto rulingIdeology = rulingParty->getIdeology();
	governmentIdeology = governmentMap.getIdeologyForCountry(oldTag, oldGovernment, rulingIdeology, debug);
	leaderIdeology = governmentMap.getLeaderIdeologyForCountry(oldTag, oldGovernment, rulingIdeology, debug);
	for (const auto& party: parties)
	{
		auto partyName = party.getName();
		auto trimmedName = partyName.substr(4, partyName.size());
		hoi4Localisations.addPoliticalPartyLocalisation(partyName, tag + "_" + trimmedName + "_party", vic2Localisations);
	}

	convertLaws();
}


void HoI4::Country::convertParties(const std::set<std::string>& majorIdeologies,
	 const governmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations)
{
	for (const auto& HoI4Ideology: majorIdeologies)
	{
		for (const auto& party: parties)
		{
			if (HoI4Ideology ==
				 governmentMap.getSupportedIdeology(governmentIdeology, party.getIdeology(), majorIdeologies))
			{
				hoi4Localisations.addPoliticalPartyLocalisation(party.getName(),
					 tag + "_" + HoI4Ideology + "_party",
					 vic2Localisations);
			}
		}
	}

	if (rulingParty != std::nullopt)
	{
		hoi4Localisations.addPoliticalPartyLocalisation(rulingParty->getName(),
			 tag + "_" + governmentIdeology + "_party",
			 vic2Localisations);
	}
}


void HoI4::Country::initIdeas(Names& names, Localisation& hoi4Localisations) const
{
	hoi4Localisations.addIdeaLocalisation(tag + "_tank_manufacturer", names.takeCarCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_motorized_equipment_manufacturer",
		 names.takeCarCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_infantry_equipment_manufacturer",
		 names.takeWeaponCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_artillery_manufacturer", names.takeWeaponCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_light_aircraft_manufacturer",
		 names.takeAircraftCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_medium_aircraft_manufacturer",
		 names.takeAircraftCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_heavy_aircraft_manufacturer",
		 names.takeAircraftCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_naval_aircraft_manufacturer",
		 names.takeAircraftCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_naval_manufacturer", names.takeNavalCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_industrial_concern", names.takeIndustryCompanyName(primaryCulture));
	hoi4Localisations.addIdeaLocalisation(tag + "_electronics_concern", names.takeElectronicCompanyName(primaryCulture));
}


void HoI4::Country::convertLaws()
{
	// mobilization laws are based on the ruling party's war policy
	if (rulingParty->getWarPolicy() == "jingoism")
	{
		mobilizationLaw = "limited_conscription";
	}
	else if (rulingParty->getWarPolicy() == "pacifism")
	{
		mobilizationLaw = "disarmed_nation";
	}

	// if at war, more economic mobilization
	if (atWar)
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


void HoI4::Country::convertLeaders(const graphicsMapper& theGraphics, const Vic2::Country& sourceCountry)
{
	auto srcLeaders = sourceCountry.getLeaders();
	for (auto srcLeader: srcLeaders)
	{
		if (srcLeader.getType() == "land")
		{
			General newLeader(srcLeader, theGraphics.getGeneralPortrait(graphicalCulture));
			generals.push_back(newLeader);
		}
		else if (srcLeader.getType() == "sea")
		{
			Admiral newLeader(srcLeader, theGraphics.getGeneralPortrait(graphicalCulture));
			admirals.push_back(newLeader);
		}
	}
}


void HoI4::Country::convertRelations(const CountryMapper& countryMap, const Vic2::Country& sourceCountry)
{
	auto srcRelations = sourceCountry.getRelations();
	for (const auto& srcRelation: srcRelations)
	{
		auto HoI4Tag = countryMap.getHoI4Tag(srcRelation.first);
		if (HoI4Tag)
		{
			HoI4::Relations newRelation(*HoI4Tag, srcRelation.second);
			relations.insert(make_pair(*HoI4Tag, std::move(newRelation)));
		}
	}
}


void HoI4::Country::convertStrategies(const CountryMapper& countryMap, const Vic2::Country& sourceCountry)
{
	for (const auto& [vic2Tag, strategy]: sourceCountry.getAI()->getConsolidatedStrategies())
	{
		if (const auto& HoI4Tag = countryMap.getHoI4Tag(vic2Tag); HoI4Tag)
		{
			HoI4::AIStrategy newStrategy("conquer", *HoI4Tag, strategy);
			conquerStrategies.push_back(newStrategy);
		}
	}

	for (const auto& srcStrategy: sourceCountry.getAI()->getStrategies())
	{
		if (const auto& HoI4Tag = countryMap.getHoI4Tag(srcStrategy.getID()); HoI4Tag)
		{
			HoI4::AIStrategy newStrategy(srcStrategy, *HoI4Tag);
			aiStrategies.push_back(newStrategy);
		}
	}
}


void HoI4::Country::convertWars(const Vic2::Country& theSourceCountry, const CountryMapper& countryMap)
{
	for (const auto& sourceWar: theSourceCountry.getWars())
	{
		War theWar(sourceWar, countryMap);
		wars.push_back(theWar);
	}
}


void HoI4::Country::determineCapitalFromVic2(const mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
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
		Log(LogLevel::Warning) << "Could not properly set capital for " << tag;
	}
}


bool HoI4::Country::attemptToPutCapitalInPreferredNonWastelandOwned(const mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
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


bool HoI4::Country::attemptToPutCapitalInNonWastelandOwned(const std::map<int, State>& allStates)
{
	for (auto ownedStateNum: states)
	{
		if (auto stateAndNum = allStates.find(ownedStateNum); stateAndNum != allStates.end())
		{
			const auto& state = stateAndNum->second;
			if ((state.getOwner() == tag) && !state.isImpassable())
			{
				capitalState = ownedStateNum;
				capitalProvince = *state.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInPreferredWastelandOwned(const mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
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


bool HoI4::Country::attemptToPutCapitalInAnyOwned(const std::map<int, State>& allStates)
{
	for (auto ownedStateNum: states)
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


bool HoI4::Country::attemptToPutCapitalInPreferredNonWastelandCored(const mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if ((state.getCores().contains(tag) || state.getClaims().contains(tag)) && !state.isImpassable())
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = (*mapping)[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyNonWastelandCored(const std::map<int, State>& allStates)
{
	for (auto ownedStateNum: states)
	{
		if (auto stateAndNum = allStates.find(ownedStateNum); stateAndNum != allStates.end())
		{
			auto state = stateAndNum->second;
			if (state.getCores().contains(tag) && !state.isImpassable())
			{
				capitalState = ownedStateNum;
				capitalProvince = *state.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInPreferredWastelandCored(const mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); mapping)
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if (state.getCores().contains(tag))
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = (*mapping)[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyCored(const std::map<int, State>& allStates)
{
	for (auto ownedStateNum: states)
	{
		if (auto state = allStates.find(ownedStateNum); state != allStates.end())
		{
			if (state->second.getCores().contains(tag))
			{
				capitalState = ownedStateNum;
				capitalProvince = *state->second.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


std::vector<std::string> HoI4::Country::getShipNames(const std::string& category) const
{
	const auto foundShipNames = shipNames.find(category);
	if (foundShipNames == shipNames.end())
	{
		return std::vector<std::string>{};
	}
	return foundShipNames->second;
}


void HoI4::Country::setCapitalRegionFlag(const Regions& regions)
{
	if (!capitalProvince)
	{
		return;
	}
	if (const auto& region = regions.getRegion(*capitalProvince); region)
	{
		flags.insert("conv_" + *region);
	}
}


void HoI4::Country::convertTechnology(const Mappers::TechMapper& techMapper,
	 const Mappers::ResearchBonusMapper& researchBonusMapper)
{
	theTechnologies = HoI4::technologies(techMapper, researchBonusMapper, oldTechnologiesAndInventions);
}


void HoI4::Country::setGovernmentToExistingIdeology(const std::set<std::string>& majorIdeologies,
	 const Ideologies& ideologies,
	 const governmentMapper& governmentMap,
	 bool debug)
{
	if (rulingParty == std::nullopt)
	{
		return;
	}

	governmentIdeology = governmentMap.getExistingIdeologyForCountry(tag,
		 oldGovernment,
		 rulingParty->getIdeology(),
		 majorIdeologies,
		 ideologies,
		 debug);
	leaderIdeology = governmentMap.getExistingLeaderIdeologyForCountry(tag,
		 oldGovernment,
		 rulingParty->getIdeology(),
		 majorIdeologies,
		 ideologies,
		 debug);
}


void HoI4::Country::createLeader(Names& names, graphicsMapper& theGraphics)
{
	for (const auto& configuredLeader: leaders)
	{
		if (configuredLeader.getIdeology() == leaderIdeology)
		{
			return;
		}
	}

	leaders.push_back(CountryLeader::Factory::createNewLeader(primaryCulture,
		 primaryCultureGroup,
		 governmentIdeology,
		 leaderIdeology,
		 names,
		 theGraphics));
}


void HoI4::Country::convertIdeologySupport(const std::set<std::string>& majorIdeologies,
	 const governmentMapper& governmentMap)
{
	ideologySupport.clear();
	if (oldTag == "AAA")
	{
		ideologySupport.insert(std::make_pair("neutrality", 100));
		return;
	}
	if (oldTag == "UCV")
	{
		ideologySupport.insert(std::make_pair("neutrality", 100));
		return;
	}

	for (const auto& upperHouseIdeology: upperHouseComposition)
	{
		auto ideology = governmentMap.getSupportedIdeology(governmentIdeology, upperHouseIdeology.first, majorIdeologies);
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
			ideologySupport.insert(std::make_pair("neutrality", 0));
			supportItr = ideologySupport.find("neutrality");
		}
		supportItr->second += remainingSupport;
	}
}


void HoI4::Country::determineShipVariants(const PossibleShipVariants& possibleVariants)
{
	theShipVariants = std::make_unique<ShipVariants>(possibleVariants, *theTechnologies, tag);
}


void HoI4::Country::convertNavies(const UnitMappings& unitMap,
	 const MtgUnitMappings& mtgUnitMap,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates,
	 const ProvinceDefinitions& provinceDefinitions,
	 const mappers::ProvinceMapper& provinceMapper)
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

	theNavies = std::make_unique<Navies>(oldArmies,
		 backupNavalLocation,
		 unitMap,
		 mtgUnitMap,
		 *theShipVariants,
		 provinceToStateIDMap,
		 allStates,
		 tag,
		 provinceDefinitions,
		 provinceMapper);

	navyNames.addLegacyShipTypeNames(LegacyShipTypeNames{"submarine", "Submarine", getShipNames("frigate")});
	navyNames.addLegacyShipTypeNames(LegacyShipTypeNames{"carrier", "Carrier", getShipNames("monitor")});
	navyNames.addLegacyShipTypeNames(LegacyShipTypeNames{"battleship", "Battleship", getShipNames("dreadnought")});
	navyNames.addLegacyShipTypeNames(LegacyShipTypeNames{"battle_cruiser", "Battlecruiser", getShipNames("ironclad")});
	navyNames.addLegacyShipTypeNames(LegacyShipTypeNames{"heavy_cruiser", "Heavy Cruiser", getShipNames("manowar")});
	navyNames.addLegacyShipTypeNames(LegacyShipTypeNames{"destroyer", "Destroyer", getShipNames("cruiser")});
	navyNames.addLegacyShipTypeNames(
		 LegacyShipTypeNames{"light_cruiser", "Light Cruiser", getShipNames("commerce_raider")});

	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_DD_HISTORICAL",
		 "NAME_THEME_HISTORICAL_DESTROYERS",
		 std::set<std::string>{"ship_hull_light destroyer"},
		 "Destroyer DD-%d",
		 getShipNames("cruiser")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_DE_HISTORICAL",
		 "NAME_THEME_HISTORICAL_DE",
		 std::set<std::string>{"ship_hull_light destroyer"},
		 "Destroyer Escort DE-%d",
		 getShipNames("cruiser")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_CL_HISTORICAL",
		 "NAME_THEME_HISTORICAL_CL",
		 std::set<std::string>{"ship_hull_cruiser light_cruiser"},
		 "Light Cruiser CL-%d",
		 getShipNames("commerce_raider")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_CL_HISTORICAL",
		 "NAME_THEME_HISTORICAL_CL",
		 std::set<std::string>{"ship_hull_cruiser light_cruiser"},
		 "Light Cruiser CL-%d",
		 getShipNames("commerce_raider")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_CA_HISTORICAL",
		 "NAME_THEME_HISTORICAL_CA",
		 std::set<std::string>{"ship_hull_cruiser heavy_cruiser"},
		 "Heavy Cruiser CA-%d",
		 getShipNames("manowar")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_CLAA_HISTORICAL",
		 "NAME_THEME_HISTORICAL_CLAA",
		 std::set<std::string>{"ship_hull_cruiser light_cruiser"},
		 "Light Cruiser CLAA-%d",
		 getShipNames("commerce_raider")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_MINELAYERS_HISTORICAL",
		 "NAME_THEME_HISTORICAL_MINELAYERS",
		 std::set<std::string>{"ship_hull_cruiser light_cruiser", "ship_hull_light destroyer"},
		 "Minelayer CM-%d",
		 getShipNames("commerce_raider")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_BB_HISTORICAL",
		 "NAME_THEME_HISTORICAL_BB",
		 std::set<std::string>{"ship_hull_heavy battleship"},
		 "Battleship BB-%d",
		 getShipNames("dreadnought")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_BC_HISTORICAL",
		 "NAME_THEME_HISTORICAL_BC",
		 std::set<std::string>{"ship_hull_heavy battle_cruiser"},
		 "Battlecruiser BC-%d",
		 getShipNames("ironclad")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_CV_HISTORICAL",
		 "NAME_THEME_HISTORICAL_CARRIERS",
		 std::set<std::string>{"ship_hull_carrier carrier"},
		 "Carrier CV-%d",
		 getShipNames("monitor")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_CVL_HISTORICAL",
		 "NAME_THEME_HISTORICAL_CVL",
		 std::set<std::string>{"ship_hull_carrier carrier"},
		 "Carrier CVL-%d",
		 getShipNames("monitor")});
	navyNames.addMtgShipTypeNames(MtgShipTypeNames{tag + "_SS_HISTORICAL",
		 "NAME_THEME_HISTORICAL_SUBMARINES",
		 std::set<std::string>{"ship_hull_submarine submarine"},
		 "Submarine SS-%d",
		 getShipNames("frigate")});
}


void HoI4::Country::convertConvoys(const UnitMappings& unitMap)
{
	for (const auto& army: oldArmies)
	{
		for (const auto& regiment: army.getUnits())
		{
			if (const auto& type = regiment.getType(); unitMap.hasMatchingType(type))
			{
				for (const auto& unitInfo: unitMap.getMatchingUnitInfo(type))
				{
					if (unitInfo.getCategory() == "convoy")
					{
						// Convoys get placed in national stockpile
						convoys = convoys + unitInfo.getSize();
						break;
					}
				}
			}
			else
			{
				Log(LogLevel::Warning) << "Unknown unit type: " << type;
			}
		}
	}
}


void HoI4::Country::convertAirForce(const UnitMappings& unitMap)
{
	static std::map<std::string, std::vector<std::string>> backups = {
		 {"fighter_equipment_0", {"tac_bomber_equipment_0"}}};
	for (const auto& army: oldArmies)
	{
		for (const auto& regiment: army.getUnits())
		{
			if (const auto& type = regiment.getType(); unitMap.hasMatchingType(type))
			{
				for (const auto& unitInfo: unitMap.getMatchingUnitInfo(type))
				{
					if (unitInfo.getCategory() == "air")
					{
						// Air units get placed in national stockpile.
						auto equip = unitInfo.getEquipment();
						auto amount = unitInfo.getSize();
						const auto& backup = backups.find(equip);
						if (backup != backups.end())
						{
							amount /= (1 + static_cast<int>(backup->second.size()));
							for (const auto& b: backup->second)
							{
								equipmentStockpile[b] += amount;
							}
						}
						equipmentStockpile[equip] += amount;
						break;
					}
				}
			}
			else
			{
				Log(LogLevel::Warning) << "Unknown unit type: " << type;
			}
		}
	}
}


void HoI4::Country::convertArmies(const militaryMappings& theMilitaryMappings,
	 const HoI4::States& theStates,
	 const mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	if (capitalProvince)
	{
		theArmy.convertArmies(theMilitaryMappings,
			 *capitalProvince,
			 theConfiguration.getForceMultiplier(),
			 *theTechnologies,
			 theStates,
			 provinceMapper);
	}
	else
	{
		theArmy.convertArmies(theMilitaryMappings,
			 0,
			 theConfiguration.getForceMultiplier(),
			 *theTechnologies,
			 theStates,
			 provinceMapper);
	}

	for (const auto& [equipmentType, amount]: theArmy.getLeftoverEquipment())
	{
		equipmentStockpile[equipmentType] += amount;
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


std::optional<HoI4::Relations> HoI4::Country::getRelations(const std::string& withWhom) const
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


void HoI4::Country::addGenericFocusTree(const std::set<std::string>& majorIdeologies)
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


float HoI4::Country::getNavalStrength() const
{
	auto navalStrength = 0.0f;

	for (const auto& navy: theNavies->getMtgNavies())
	{
		navalStrength += navy.getStrength();
	}

	return navalStrength;
}


double HoI4::Country::getEconomicStrength(const double& years) const
{
	constexpr auto militaryFactoriesPerYear = 0.469f;
	constexpr auto factoriesUsedForConsumerGoods = 0.5f;
	constexpr auto daysPerYear = 365;

	const auto militarySectorStrength = militaryFactories * 3 * daysPerYear * years;
	const auto civilianSectorStrength = civilianFactories * militaryFactoriesPerYear * factoriesUsedForConsumerGoods *
													factoriesUsedForConsumerGoods * 3 * daysPerYear * years * years;

	return militarySectorStrength + civilianSectorStrength;
}


bool HoI4::Country::areElectionsAllowed() const
{
	return (governmentIdeology == "democratic") ||
			 ((governmentIdeology == "neutrality") &&
				  ((leaderIdeology == "conservatism_neutral") || (leaderIdeology == "liberalism_neutral") ||
						(leaderIdeology == "socialism_neutral")));
}


std::optional<HoI4::Faction> HoI4::Country::getFaction() const
{
	if (faction)
	{
		return std::make_optional(*faction);
	}
	else
	{
		return std::nullopt;
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
		return std::nullopt;
	}
}

// Calculates Influence Factor = Σ Outside Influence - 1.5 * Leader Influence
double HoI4::Country::calculateInfluenceFactor()
{
	if (sphereLeader.empty())
	{
		Log(LogLevel::Debug) << tag << " has no sphere leader set";
		return 55.5;
	}
	else
	{
		double influenceFactor = 0;
		for (auto& influenceItr: GPInfluences)
		{
			if (influenceItr.first != sphereLeader)
			{
				influenceFactor += influenceItr.second;
			}
			if (influenceItr.first == sphereLeader)
			{
				influenceFactor -= 1.5 * influenceItr.second;
			}
		}
		// 1 is used because if freedom_level is too close to 0 (how close?)
		// it's displayed ingame as being halfway: 0.5 instead of 0.0000something
		return std::clamp(influenceFactor, 1.0, 100.0);
	}
}
