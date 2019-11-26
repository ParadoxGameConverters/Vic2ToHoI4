#include "HoI4Country.h"
#include "Advisor.h"
#include "HoI4World.h"
#include "Log.h"
#include "HoI4Faction.h"
#include "HoI4Focus.h"
#include "HoI4Leader.h"
#include "HoI4Localisation.h"
#include "HoI4War.h"
#include "Names.h"
#include "MilitaryMappings/MilitaryMappings.h"
#include "../Mappers/CountryMapping.h"
#include "../Mappers/GovernmentMapper.h"
#include "../Mappers/GraphicsMapper.h"
#include "../Mappers/ProvinceDefinitions.h"
#include "../Mappers/TechMapper.h"
#include "../Mappers/V2Localisations.h"
#include "../V2World/Country.h"
#include "../V2World/Relations.h"
#include "../V2World/Party.h"
#include "../V2World/World.h"
#include "../Mappers/Provinces/ProvinceMapper.h"
#include "OSCompatibilityLayer.h"
#include <algorithm>



void HoI4::Country::initFromV2Country(
	const Vic2::World& _srcWorld,
	const Vic2::Country* _srcCountry,
	const std::map<int, int>& stateMap,
	const std::map<int, HoI4::State>& states,
	HoI4::namesMapper& theNames,
	const graphicsMapper& theGraphics,
	const CountryMapper& countryMap,
	const mappers::FlagsToIdeasMapper& flagsToIdeasMapper
) {
	srcCountry = _srcCountry;

	determineFilename();

	human = srcCountry->isHuman();
	color = srcCountry->getColor();
	civilized = srcCountry->isCivilized();
	threat = srcCountry->getBadBoy() / 10.0;
	auto possibleGraphicalCulture = theGraphics.getGraphicalCulture(srcCountry->getPrimaryCultureGroup());
	if (possibleGraphicalCulture)
	{
		graphicalCulture = *possibleGraphicalCulture;
	}
	else
	{
		graphicalCulture = "western_european_gfx";
	}
	auto possibleGraphicalCulture2d = theGraphics.get2dGraphicalCulture(srcCountry->getPrimaryCultureGroup());
	if (possibleGraphicalCulture2d)
	{
		graphicalCulture2d = *possibleGraphicalCulture2d;
	}
	else
	{
		graphicalCulture2d = "western_european_2d";
	}
	lastElection = srcCountry->getLastElection();
	initIdeas(theNames);

	stability = 60;
	warSupport = 60;

	if (srcCountry->getProvinces().size() > 0)
	{
		/*stability -= (srcCountry->getAverageMilitancy() / 10 / 1.5);
		if (stability < 0.15)
		{
			stability = 0.15;
		}
		LOG(LogLevel::Debug) << "stability," << tag << "," << stability;
		*/
		float warAttitude = srcCountry->getAverageIssueSupport("jingoism");
		warAttitude += srcCountry->getAverageIssueSupport("pro_military") / 2;
		warAttitude -= srcCountry->getAverageIssueSupport("anti_military") / 2;
		warAttitude -= srcCountry->getAverageIssueSupport("pacifism");
		warSupport += static_cast<int>(
			(warAttitude * 0.375) + (srcCountry->getRevanchism() / 5.0) - (srcCountry->getWarExhaustion() / 100.0 / 2.5)
			);
		if (warSupport < 15)
		{
			warSupport = 15;
		}
	}

	for (auto flag: srcCountry->getFlags())
	{
		auto possibleIdea = flagsToIdeasMapper.getIdea(flag);
		if (possibleIdea)
		{
			ideas.insert(*possibleIdea);
		}
	}

	convertLaws();
	convertLeaders(theGraphics);
	convertRelations(countryMap);
	convertWars((*_srcCountry), countryMap);

	determineCapitalFromVic2(stateMap, states);

	theArmy.addSourceArmies(srcCountry->getArmies());
}


void HoI4::Country::determineFilename()
{
	auto possibleFilename = srcCountry->getName("english");
	if (possibleFilename)
	{
		filename = Utils::convertWin1252ToUTF8(*possibleFilename);
		int pipe = filename.find_first_of('|');
		while (pipe != string::npos)
		{
			filename.replace(pipe, 1, "");
			pipe = filename.find_first_of('|');
		}
		int greater = filename.find_first_of('>');
		while (greater != string::npos)
		{
			filename.replace(greater, 1, "");
			greater = filename.find_first_of('>');
		}
		int lesser = filename.find_first_of('<');
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
	auto possibleRulingParty = srcCountry->getRulingParty(sourceWorld.getParties());
	if (!possibleRulingParty)
	{
		LOG(LogLevel::Error) << "Could not find the ruling party for " << srcCountry->getTag() << ". Most likely a mod was not included.";
		LOG(LogLevel::Error) << "Double-check your settings, and remember to include EU4 to Vic2 mods. See the FAQ for more information.";
		exit(-1);
	}
	else
	{
		rulingParty = *possibleRulingParty;
	}

	governmentIdeology = governmentMap.getIdeologyForCountry(srcCountry, rulingParty.getIdeology());
	leaderIdeology = governmentMap.getLeaderIdeologyForCountry(srcCountry, rulingParty.getIdeology());
	parties = srcCountry->getActiveParties(sourceWorld.getParties());
	for (auto party: parties)
	{
		string partyName = party.getName();
		string trimmedName = partyName.substr(4, partyName.size());
		HoI4Localisation::addPoliticalPartyLocalisation(partyName, tag + "_" + trimmedName + "_party");
	}
}


void HoI4::Country::convertParties(const set<string>& majorIdeologies, const governmentMapper& governmentMap)
{
	for (auto HoI4Ideology: majorIdeologies)
	{
		for (auto party: parties)
		{
			if (governmentMap.getSupportedIdeology(governmentIdeology, party.getIdeology(), majorIdeologies) == HoI4Ideology)
			{
				HoI4Localisation::addPoliticalPartyLocalisation(party.getName(), tag + "_" + HoI4Ideology + "_party");
			}
		}
	}
	HoI4Localisation::addPoliticalPartyLocalisation(rulingParty.getName(), tag + "_" + governmentIdeology + "_party");
}


void HoI4::Country::initIdeas(HoI4::namesMapper& theNames)
{
	HoI4Localisation::addIdeaLocalisation(tag + "_tank_manufacturer", theNames.takeCarCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_motorized_equipment_manufacturer", theNames.takeCarCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_infantry_equipment_manufacturer", theNames.takeWeaponCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_artillery_manufacturer", theNames.takeWeaponCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_light_aircraft_manufacturer", theNames.takeAircraftCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_medium_aircraft_manufacturer", theNames.takeAircraftCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_heavy_aircraft_manufacturer", theNames.takeAircraftCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_naval_aircraft_manufacturer", theNames.takeAircraftCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_naval_manufacturer", theNames.takeNavalCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_industrial_concern", theNames.takeIndustryCompanyName(srcCountry->getPrimaryCulture()));
	HoI4Localisation::addIdeaLocalisation(tag + "_electronics_concern", theNames.takeElectronicCompanyName(srcCountry->getPrimaryCulture()));
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

	// if at war, more ecomonic mobilization
	if (srcCountry->isAtWar())
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
	auto srcLeaders = srcCountry->getLeaders();
	for (auto srcLeader: srcLeaders)
	{
		if (srcLeader->getType() == "land")
		{
			HoI4::General newLeader(srcLeader, theGraphics.getGeneralPortrait(graphicalCulture));
			generals.push_back(newLeader);
		}
		else if (srcLeader->getType() == "sea")
		{
			HoI4::Admiral newLeader(srcLeader, theGraphics.getGeneralPortrait(graphicalCulture));
			admirals.push_back(newLeader);
		}
	}

	theConfiguration.setLeaderIDForNextCountry();
}


void HoI4::Country::convertRelations(const CountryMapper& countryMap)
{
	auto srcRelations = srcCountry->getRelations();
	for (auto srcRelation: srcRelations)
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
	for (auto sourceWar: sourceCountry.getWars())
	{
		HoI4::War theWar(sourceWar, countryMap);
		wars.push_back(theWar);
	}
}


void HoI4::Country::determineCapitalFromVic2(const map<int, int>& provinceToStateIDMap, const map<int, HoI4::State>& states)
{
	int oldCapital = srcCountry->getCapital();
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital))
	{
		auto capitalStateMapping = provinceToStateIDMap.find((*mapping)[0]);
		if (capitalStateMapping != provinceToStateIDMap.end() && isStateValidForCapital(capitalStateMapping->second, states))
		{
			capitalStateNum = capitalStateMapping->second;
			if (isThisStateOwnedByUs(states.find(capitalStateNum)->second))
			{
				setCapitalInCapitalState((*mapping)[0]);
			}
		}
		else
		{
			findBestCapital();
		}
	}
}


bool HoI4::Country::isStateValidForCapital(int stateNum, const map<int, HoI4::State>& states)
{
	auto state = states.find(stateNum)->second;
	return (isThisStateOwnedByUs(state) || isThisStateACoreWhileWeOwnNoStates(state));
}


bool HoI4::Country::isThisStateOwnedByUs(const HoI4::State& state) const
{
	return (state.getOwner() == tag);
}


bool HoI4::Country::isThisStateACoreWhileWeOwnNoStates(const HoI4::State& state) const
{
	for (auto core: state.getCores())
	{
		if (core == tag)
		{
			return true;
		}
	}

	return false;
}


void HoI4::Country::setCapitalInCapitalState(int capitalProvince)
{
	if (auto capitalState = states.find(capitalStateNum); capitalState != states.end())
	{
		capitalState->second.setVPLocation(capitalProvince);
	}
}


void HoI4::Country::findBestCapital()
{
	capitalStateNum = 0;
	LOG(LogLevel::Warning) << "Could not properly set capital for " << tag;
}


void HoI4::Country::convertTechnology(std::unique_ptr<mappers::techMapper>& theTechMapper)
{
	auto oldTechs = srcCountry->getTechs();
	auto oldInventions = srcCountry->getInventions();
	technologies = std::make_unique<HoI4::technologies>(theTechMapper, oldTechs, oldInventions);
}


void HoI4::Country::setGovernmentToExistingIdeology(const set<string>& majorIdeologies, const map<string, HoI4Ideology*>& ideologies, const governmentMapper& governmentMap)
{
	governmentIdeology = governmentMap.getExistingIdeologyForCountry(srcCountry, rulingParty.getIdeology(), majorIdeologies, ideologies);
	leaderIdeology = governmentMap.getExistingLeaderIdeologyForCountry(srcCountry, rulingParty.getIdeology(), majorIdeologies, ideologies);
}


void HoI4::Country::convertIdeologySupport(const set<string>& majorIdeologies, const governmentMapper& governmentMap)
{
	for (auto upperHouseIdeology: srcCountry->getUpperHouseComposition())
	{
		string ideology = governmentMap.getSupportedIdeology(governmentIdeology, upperHouseIdeology.first, majorIdeologies);
		auto supportItr = ideologySupport.find(ideology);
		if (supportItr == ideologySupport.end())
		{
			ideologySupport.insert(make_pair(ideology, 0));
			supportItr = ideologySupport.find(ideology);
		}
		supportItr->second += static_cast<int>(upperHouseIdeology.second * 100);
	}

	int remainingSupport = 100;
	for (auto ideology: ideologySupport)
	{
		remainingSupport -= ideology.second;
	}
	auto supportItr = ideologySupport.find("neutrality");
	if (supportItr == ideologySupport.end())
	{
		ideologySupport.insert(make_pair("neutrality", 0));
		supportItr = ideologySupport.find("neutrality");
	}
	supportItr->second += remainingSupport;
}


void HoI4::Country::determineShipVariants(const std::vector<HoI4::shipVariant>& possibleVariants)
{
	theShipVariants = std::make_unique<HoI4::shipVariants>(possibleVariants, *technologies, tag);
}


void HoI4::Country::convertNavies(
	const HoI4::UnitMappings& unitMap,
	const HoI4::MtgUnitMappings& mtgUnitMap,
	const HoI4::coastalProvinces& theCoastalProvinces,
	const std::map<int, int>& provinceToStateIDMap)
{
	int backupNavalLocation = 0;
	for (auto state: states)
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

	theNavies = std::make_unique<HoI4::Navies>(
		srcCountry->getArmies(),
		backupNavalLocation,
		unitMap,
		mtgUnitMap,
		*theShipVariants,
		theCoastalProvinces,
		provinceToStateIDMap,
		states,
		tag);
}


void HoI4::Country::convertConvoys(const HoI4::UnitMappings& unitMap)
{
	for (auto army : srcCountry->getArmies())
	{
		for (auto regiment : army->getRegiments())
		{
			string type = regiment->getType();

			if (unitMap.hasMatchingType(type))
			{
				HoI4::HoI4UnitType unitInfo = unitMap.getMatchingUnitInfo(type);

				if (unitInfo.getCategory() == "convoy")
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


void HoI4::Country::convertAirforce(const HoI4::UnitMappings& unitMap)
{
        static std::map<std::string, vector<std::string>> backups = {
            {"fighter_equipment_0", {"tac_bomber_equipment_0"}}};
        for (auto army : srcCountry->getArmies())
	{
		for (auto regiment : army->getRegiments())
		{
			string type = regiment->getType();

			if (unitMap.hasMatchingType(type))
			{
				HoI4::HoI4UnitType unitInfo = unitMap.getMatchingUnitInfo(type);

                                if (unitInfo.getCategory() != "air")
                                {
                                        continue;
                                }

                                // Air units get placed in national stockpile.
                                string equip = unitInfo.getEquipment();
                                int amount = unitInfo.getSize();
                                const auto& bkup = backups.find(equip);
                                if (bkup != backups.end())
                                {
                                  amount /= (1 + bkup->second.size());
                                        for (const auto& b : bkup->second)
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


void HoI4::Country::convertArmies(const HoI4::militaryMappings& theMilitaryMappings)
{
	std::optional<int> backupLocation;
	if (auto capitalState = states.find(capitalStateNum); capitalState != states.end())
	{
		backupLocation = capitalState->second.getVPLocation();
	}
	if (backupLocation)
	{
		theArmy.convertArmies(theMilitaryMappings, *backupLocation, theConfiguration.getForceMultiplier());
	}
	else
	{
		theArmy.convertArmies(theMilitaryMappings, 0, theConfiguration.getForceMultiplier());
	}
}


void HoI4::Country::addState(HoI4::State& state)
{
	states.insert(std::make_pair(state.getID(), state));

	if (capitalStateNum == 0)
	{
		capitalStateNum = state.getID();
		state.setAsCapitalState();
	}

	for (const auto province: state.getProvinces())
	{
		addProvince(province);
	}
}


void HoI4::Country::addProvince(int _province)
{
	provinces.insert(_province);
}


optional<HoI4Relations> HoI4::Country::getRelations(string withWhom) const
{
	map<string, HoI4Relations>::const_iterator i = relations.find(withWhom);
	if (i != relations.end())
	{
		return i->second;
	}
	else
	{
		return {};
	}
}


void HoI4::Country::calculateIndustry()
{
	for (auto state: states)
	{
		civilianFactories += state.second.getCivFactories();
		militaryFactories += state.second.getMilFactories();
		dockyards += state.second.getDockyards();
	}
}


void HoI4::Country::addVPsToCapital(int VPs)
{
	if (auto capitalState = states.find(capitalStateNum); capitalState != states.end())
	{
		capitalState->second.addVictoryPointValue(VPs);
	}
}


void HoI4::Country::addGenericFocusTree(const std::set<string>& majorIdeologies)
{
	if (!nationalFocus)
	{
		HoI4FocusTree genericNationalFocus(*this);
		genericNationalFocus.addGenericFocusTree(majorIdeologies);
		nationalFocus = std::move(genericNationalFocus.makeCustomizedCopy(*this));
	}
}


void HoI4::Country::adjustResearchFocuses()
{
	if (greatPower && (nationalFocus != nullptr))
	{
		nationalFocus->removeFocus("extra_tech_slot_2" + tag);
	}
}


void HoI4::Country::addAirbasesToCapital(int airbases)
{
	if (auto capitalState = states.find(capitalStateNum); capitalState != states.end())
	{
		capitalState->second.addAirBase(airbases);
	}
}


double HoI4::Country::getStrengthOverTime(double years) const
{
	return getMilitaryStrength() + getEconomicStrength(years);
}


double HoI4::Country::getMilitaryStrength() const
{
	return 0.0;
}


double HoI4::Country::getEconomicStrength(double years) const
{
	double militarySectorStrength = militaryFactories * 3 * 365 * years;
	double civilianSectorStrength = civilianFactories * 0.469 * 0.5 * 3 * 365 * 0.5 * years * years; /*.469 is milfac per year, .5 since half are used by consumer goods*/

	return militarySectorStrength + civilianSectorStrength;
}


bool HoI4::Country::areElectionsAllowed() const
{
	if (
			(governmentIdeology == "democratic") ||
			(
				(governmentIdeology == "neutrality") &&
				(
					(leaderIdeology == "conservatism_neutral") ||
					(leaderIdeology == "liberalism_neutral") ||
					(leaderIdeology == "socialism_neutral")
				)
			)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


std::optional<const HoI4::State> HoI4::Country::getCapitalState() const
{
	if (auto capitalState = states.find(capitalStateNum); capitalState != states.end())
	{
		return capitalState->second;
	}
	else
	{
		return std::nullopt;
	}
}