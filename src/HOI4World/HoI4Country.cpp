#include "src/HOI4World/HoI4Country.h"
#include "external/common_items/CommonFunctions.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/HOI4World/Diplomacy/HoI4War.h"
#include "src/HOI4World/HoI4Localisation.h"
#include "src/HOI4World/HoI4World.h"
#include "src/HOI4World/MilitaryMappings/MilitaryMappings.h"
#include "src/HOI4World/Names/Names.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/Government/GovernmentMapper.h"
#include "src/Mappers/Graphics/GraphicsMapper.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Mappers/Technology/TechMapper.h"
#include "src/V2World/Ai/AI.h"
#include "src/V2World/Ai/AIStrategy.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/Politics/Party.h"
#include "src/V2World/World/World.h"
#include <algorithm>
#include <cmath>
#include <ranges>

#include "src/HOI4World/Characters/CharacterFactory.h"


HoI4::Country::Country(std::string tag,
	 const Vic2::Country& sourceCountry,
	 Names& names,
	 Mappers::GraphicsMapper& graphicsMapper,
	 const Mappers::CountryMapper& countryMap,
	 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
	 Localisation& hoi4Localisations,
	 const date& startDate,
	 const Mappers::ProvinceMapper& theProvinceMapper,
	 const States& worldStates,
	 Character::Factory& characterFactory):
	 tag(std::move(tag)), name_(sourceCountry.getName("english")), adjective_(sourceCountry.getAdjective("english")),
	 oldTag(sourceCountry.getTag()), human(human = sourceCountry.isHuman()), threat(sourceCountry.getBadBoy() / 10.0),
	 oldCapital(sourceCountry.getCapital()), primaryCulture(sourceCountry.getPrimaryCulture().value_or("no_culture")),
	 civilized(sourceCountry.isCivilized()),
	 primaryCultureGroup(sourceCountry.getPrimaryCultureGroup().value_or("no_culture")),
	 rulingParty(sourceCountry.getRulingParty()), parties(sourceCountry.getActiveParties()),
	 oldGovernment(sourceCountry.getGovernment()), upperHouseComposition(sourceCountry.getUpperHouseComposition()),
	 lastElection(sourceCountry.getLastElection())
{
	std::seed_seq seed{tag[0], tag[1], tag[2]};
	generator.seed(seed);

	determineFilename();

	const auto& sourceColor = sourceCountry.getColor();
	if (sourceColor)
	{
		color = *sourceColor;
	}
	auto possibleGraphicalCulture = graphicsMapper.getGraphicalCulture(primaryCulture, primaryCultureGroup);
	if (possibleGraphicalCulture)
	{
		graphicalCulture = *possibleGraphicalCulture;
	}
	auto possibleGraphicalCulture2d = graphicsMapper.get2dGraphicalCulture(primaryCulture, primaryCultureGroup);
	if (possibleGraphicalCulture2d)
	{
		graphicalCulture2d = *possibleGraphicalCulture2d;
	}
	armyPortraits = graphicsMapper.getArmyPortraits(primaryCulture, primaryCultureGroup);
	navyPortraits = graphicsMapper.getNavyPortraits(primaryCulture, primaryCultureGroup);
	femaleMilitaryPortraits = graphicsMapper.getFemalePortraits(primaryCulture, primaryCultureGroup, "military");
	femaleMonarchPortraits = graphicsMapper.getFemalePortraits(primaryCulture, primaryCultureGroup, "monarch");
	femaleIdeologicalPortraits =
		 graphicsMapper.getFemalePortraits(primaryCulture, primaryCultureGroup, "ideological_leader");
	maleCommunistPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "communism");
	maleDemocraticPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "democratic");
	maleFascistPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "fascism");
	maleAbsolutistPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "absolutist");
	maleNeutralPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "neutrality");
	maleRadicalPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "radical");
	communistAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "communism");
	democraticAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "democratic");
	neutralityAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "neutrality");
	absolutistAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "absolutist");
	radicalAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "radical");
	fascistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "fascism");

	initIdeas(names, hoi4Localisations);

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

	lastDynasty = sourceCountry.getLastDynasty();
	if (const auto& lastMonarch = sourceCountry.getLastMonarch(); lastMonarch && hasRulingDynasty())
	{
		convertMonarch(*lastMonarch);
	}
	convertLeaders(sourceCountry, characterFactory, graphicsMapper, hoi4Localisations);
	convertRelations(countryMap, sourceCountry, startDate);
	atWar = sourceCountry.isAtWar();

	employedWorkers = sourceCountry.getEmployedWorkers();

	oldArmies = sourceCountry.getArmies();
	theArmy.addSourceArmies(oldArmies);
	shipNames = sourceCountry.getAllShipNames();

	sourceCountryGoods = sourceCountry.getGoodsStockpile();

	createOperatives(graphicsMapper, names);
}


HoI4::Country::Country(const std::shared_ptr<Country> owner,
	 const std::string& region_,
	 const Regions& regions,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names):
	 primaryCulture(owner->primaryCulture), primaryCultureGroup(owner->primaryCultureGroup), civilized(owner->civilized),
	 rulingParty(owner->rulingParty), parties(owner->parties), upperHouseComposition(owner->upperHouseComposition),
	 lastElection(owner->lastElection), color(owner->color), graphicalCulture(owner->graphicalCulture),
	 graphicalCulture2d(owner->graphicalCulture2d), warSupport(owner->warSupport),
	 oldTechnologiesAndInventions(owner->oldTechnologiesAndInventions), atWar(owner->atWar), shipNames(owner->shipNames),
	 generatedDominion(true), region(region_), puppetMaster(owner), puppetMasterOldTag(owner->getOldTag()),
	 governmentIdeology(owner->getGovernmentIdeology()), leaderIdeology(owner->getLeaderIdeology()), oldCapital(-1)
{
	if (const auto& regionName = regions.getRegionName(region); regionName)
	{
		if (const auto& ownerAdjective = owner->adjective_; ownerAdjective)
		{
			name_ = *ownerAdjective + " " + *regionName;
		}
		else
		{
			name_ = *regionName;
		}
	}

	if (const auto& regionAdjective = regions.getRegionAdjective(region); regionAdjective)
	{
		adjective_ = *regionAdjective;
	}

	auto hsv = color.getHsvComponents();
	if (hsv[2] > 0.2F)
	{
		hsv[2] -= 0.2F;
	}
	else
	{
		hsv[2] += 0.2F;
	}
	color = commonItems::Color(hsv);

	armyPortraits = graphicsMapper.getArmyPortraits(primaryCulture, primaryCultureGroup);
	navyPortraits = graphicsMapper.getNavyPortraits(primaryCulture, primaryCultureGroup);
	femaleMilitaryPortraits = graphicsMapper.getFemalePortraits(primaryCulture, primaryCultureGroup, "military");
	femaleMonarchPortraits = graphicsMapper.getFemalePortraits(primaryCulture, primaryCultureGroup, "monarch");
	femaleIdeologicalPortraits =
		 graphicsMapper.getFemalePortraits(primaryCulture, primaryCultureGroup, "ideological_leader");
	maleCommunistPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "communism");
	maleDemocraticPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "democratic");
	maleFascistPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "fascism");
	maleAbsolutistPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "absolutist");
	maleNeutralPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "neutrality");
	maleRadicalPortraits = graphicsMapper.getLeaderPortraits(primaryCulture, primaryCultureGroup, "radical");
	communistAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "communism");
	democraticAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "democratic");
	fascistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "fascism");
	absolutistAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "absolutist");
	neutralityAdvisorPortrait =
		 graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "neutrality");
	radicalAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCulture, primaryCultureGroup, "radical");

	createOperatives(graphicsMapper, names);

	convertLaws();
}


HoI4::Country::Country(const std::string& region_,
	 const Regions& regions,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names):
	 primaryCulture("unrecognized"), primaryCultureGroup("unrecognized"), unrecognizedNation(true), region(region_),
	 oldCapital(-1)
{
	if (const auto& regionName = regions.getRegionName(region); regionName)
	{
		name_ = "Unrecognized " + *regionName;
	}

	if (const auto& regionAdjective = regions.getRegionAdjective(region); regionAdjective)
	{
		adjective_ = *regionAdjective;
	}

	color = commonItems::Color(std::array{128, 128, 128});
}


void HoI4::Country::determineFilename()
{
	if (name_)
	{
		filename = commonItems::convertWin1252ToUTF8(*name_);
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
	 const Mappers::GovernmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names,
	 std::mt19937& femaleChanceGenerator,
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
	convertMonarchIdea(graphicsMapper, names, hoi4Localisations, femaleChanceGenerator);
}


void HoI4::Country::convertParties(const std::set<std::string>& majorIdeologies,
	 const Mappers::IdeologyMapper& ideologyMapper,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations)
{
	for (const auto& HoI4Ideology: majorIdeologies)
	{
		for (const auto& party: parties)
		{
			if (HoI4Ideology ==
				 ideologyMapper.getSupportedIdeology(governmentIdeology, party.getIdeology(), majorIdeologies))
			{
				hoi4Localisations.addPoliticalPartyLocalisation(party.getName(),
					 tag + "_" + HoI4Ideology + "_party",
					 vic2Localisations);
			}
		}
	}

	if (rulingParty != std::nullopt)
	{
		const auto& HoI4Key = tag + "_" + governmentIdeology + "_party";
		if (hasRulingDynasty())
		{
			hoi4Localisations.addRulingHouseLocalisations(HoI4Key, *lastDynasty);
		}
		else
		{
			hoi4Localisations.addPoliticalPartyLocalisation(rulingParty->getName(), HoI4Key, vic2Localisations);
		}
	}
}


bool HoI4::Country::hasRulingDynasty()
{
	if (lastDynasty && oldGovernment == "absolute_monarchy")
	{
		return true;
	}
	return false;
}


void HoI4::Country::initIdeas(Names& names, Localisation& hoi4Localisations)
{
	if (const auto name = names.takeCarCompanyName(primaryCulture, generator); name.has_value())
	{
		has_tank_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_tank_manufacturer", name);
	}
	if (const auto name = names.takeCarCompanyName(primaryCulture, generator); name.has_value())
	{
		has_motorized_equipment_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_motorized_equipment_manufacturer", name);
	}
	if (const auto name = names.takeWeaponCompanyName(primaryCulture, generator); name.has_value())
	{
		has_infantry_equipment_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_infantry_equipment_manufacturer", name);
	}
	if (const auto name = names.takeWeaponCompanyName(primaryCulture, generator); name.has_value())
	{
		has_artillery_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_artillery_manufacturer", name);
	}
	if (const auto name = names.takeAircraftCompanyName(primaryCulture, generator); name.has_value())
	{
		has_light_aircraft_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_light_aircraft_manufacturer", name);
	}
	if (const auto name = names.takeAircraftCompanyName(primaryCulture, generator); name.has_value())
	{
		has_medium_aircraft_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_medium_aircraft_manufacturer", name);
	}
	if (const auto name = names.takeAircraftCompanyName(primaryCulture, generator); name.has_value())
	{
		has_heavy_aircraft_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_heavy_aircraft_manufacturer", name);
	}
	if (const auto name = names.takeAircraftCompanyName(primaryCulture, generator); name.has_value())
	{
		has_naval_aircraft_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_naval_aircraft_manufacturer", name);
	}
	if (const auto name = names.takeNavalCompanyName(primaryCulture, generator); name.has_value())
	{
		has_naval_manufacturer_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_naval_manufacturer", name);
	}
	if (const auto name = names.takeIndustryCompanyName(primaryCulture, generator); name.has_value())
	{
		has_industrial_concern_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_industrial_concern", name);
	}
	if (const auto name = names.takeElectronicCompanyName(primaryCulture, generator); name.has_value())
	{
		has_electronics_concern_ = true;
		hoi4Localisations.addIdeaLocalisation(tag + "_electronics_concern", name);
	}
}


void HoI4::Country::createOperatives(const Mappers::GraphicsMapper& graphicsMapper, Names& names)
{
	for (const auto& operativePortrait: graphicsMapper.getFemaleOperativePortraits(primaryCulture, primaryCultureGroup))
	{
		const auto firstName = names.getFemaleName(primaryCulture, generator);
		if (!firstName)
		{
			break;
		}

		auto surname = names.getFemaleSurname(primaryCulture, generator);
		if (!surname)
		{
			surname = names.getSurname(primaryCulture, generator);
		}
		if (!surname)
		{
			break;
		}

		const std::string name = *firstName + " " + *surname;
		operatives_.push_back(Operative(name, operativePortrait, /*female=*/true, tag));
		if (operatives_.size() > 2)
		{
			break;
		}
	}

	for (const auto& operativePortrait: graphicsMapper.getMaleOperativePortraits(primaryCulture, primaryCultureGroup))
	{
		const auto firstName = names.getMaleName(primaryCulture, generator);
		if (!firstName)
		{
			break;
		}

		auto surname = names.getSurname(primaryCulture, generator);
		if (!surname)
		{
			break;
		}

		const std::string name = *firstName + " " + *surname;
		operatives_.push_back(Operative(name, operativePortrait, /*female=*/false, tag));
		if (operatives_.size() > 4)
		{
			break;
		}
	}
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


void HoI4::Country::convertMonarch(const std::string& lastMonarch)
{
	const auto newLastMonarch = commonItems::convertWin1252ToUTF8(lastMonarch);

	nextMonarch = std::make_pair(newLastMonarch, "");
	const auto& lastSpacePos = newLastMonarch.find_last_of(" ");
	if (lastSpacePos == std::string::npos)
	{
		return;
	}

	const auto& regnalName = newLastMonarch.substr(0, lastSpacePos);
	const auto& potentialRegnalNumber = newLastMonarch.substr(lastSpacePos + 1, newLastMonarch.size());
	for (int i = 0; i < 30; ++i)
	{
		if (!potentialRegnalNumber.empty() && cardinalToRoman(i) == potentialRegnalNumber)
		{
			nextMonarch = std::make_pair(regnalName, cardinalToRoman(i + 1));
			break;
		}
	}
}


void HoI4::Country::convertLeaders(const Vic2::Country& sourceCountry,
	 Character::Factory& characterFactory,
	 const Mappers::GraphicsMapper& graphics_mapper,
	 Localisation& localisation)
{
	const auto army_portraits = graphics_mapper.getArmyPortraits(primaryCulture, primaryCultureGroup);
	const auto navy_portraits = graphics_mapper.getNavyPortraits(primaryCulture, primaryCultureGroup);
	if (army_portraits.empty() || navy_portraits.empty())
	{
		Log(LogLevel::Warning) << "No portraits for culture " << primaryCulture;
		return;
	}

	for (const auto& srcLeader: sourceCountry.getLeaders())
	{
		if (srcLeader.getType() == "land")
		{
			Character newCommander = characterFactory.createNewGeneral(srcLeader,
				 tag,
				 army_portraits[std::uniform_int_distribution<int>{0, static_cast<int>(army_portraits.size() - 1)}(
					  generator)],
				 localisation);
			characters_.push_back(newCommander);
		}
		else if (srcLeader.getType() == "sea")
		{
			Character newAdmiral = characterFactory.createNewAdmiral(srcLeader,
				 tag,
				 navy_portraits[std::uniform_int_distribution<int>{0, static_cast<int>(navy_portraits.size() - 1)}(
					  generator)],
				 localisation);
			characters_.push_back(newAdmiral);
		}
	}
}


void HoI4::Country::convertMonarchIdea(const Mappers::GraphicsMapper& graphicsMapper,
	 Names& names,
	 Localisation& hoi4Localisations,
	 std::mt19937& femaleChanceGenerator)
{
	if (!hasMonarchIdea())
	{
		return;
	}

	std::optional<std::string> firstName;
	std::optional<std::string> surname = lastDynasty;

	bool female = std::uniform_int_distribution{1, 20}(femaleChanceGenerator) == 20;
	if (female)
	{
		firstName = names.getFemaleName(primaryCulture, generator);
		auto femaleSurname = names.getFemaleSurname(primaryCulture, generator);
		if (!firstName)
		{
			firstName = names.getMaleName(primaryCulture, generator);
			if (!surname)
			{
				surname = names.getSurname(primaryCulture, generator);
			}
			female = false;
		}
		else if (!surname)
		{
			if (femaleSurname)
			{
				surname = femaleSurname;
			}
			else
			{
				surname = names.getSurname(primaryCulture, generator);
			}
		}
	}
	else
	{
		firstName = names.getMaleName(primaryCulture, generator);
		auto newSurname = names.getSurname(primaryCulture, generator);

		if (!firstName)
		{
			firstName = names.getFemaleName(primaryCulture, generator);
			if (auto femaleSurname = names.getFemaleSurname(primaryCulture, generator); femaleSurname)
			{
				newSurname = femaleSurname;
			}
			female = true;
		}

		if (!surname)
		{
			surname = newSurname;
		}
	}

	if (!firstName || !surname)
	{
		return;
	}

	if (!female)
	{
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "King " + *firstName + " " + *surname, "english");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Rei " + *firstName + " " + *surname, "braz_por");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Roi " + *firstName + " " + *surname, "french");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "König " + *firstName + " " + *surname, "german");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Król " + *firstName + " " + *surname, "polish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Король " + *firstName + " " + *surname, "russian");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Rey " + *firstName + " " + *surname, "spanish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", *firstName + " " + *surname + "王", "japanese");
	}
	else
	{
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Queen " + *firstName + " " + *surname, "english");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Rainha " + *firstName + " " + *surname, "braz_por");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Reine " + *firstName + " " + *surname, "french");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Königin " + *firstName + " " + *surname, "german");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Królowa " + *firstName + " " + *surname, "polish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Королева " + *firstName + " " + *surname, "russian");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", "Reina " + *firstName + " " + *surname, "spanish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch", *firstName + " " + *surname + "女王", "japanese");
	}

	if (!female)
	{
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Rallying around the King of [" + tag + ".GetName] and the [" + tag + ".GetAdjective] Dominions, the [" +
				  tag + ".GetAdjective] people stand united and proud of their imperial legacy.",
			 "english");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Reunindo-se em torno do Rei da [" + tag + ".GetName] e dos Domínios [" + tag + ".GetAdjective], o povo [" +
				  tag + ".GetAdjective] se mantém unido e orgulhoso de seu legado imperial.",
			 "braz_por");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Rassemblant autour du Roi de [" + tag + ".GetName] et des colonies [" + tag +
				  ".GetAdjective]s, la nation [" + tag + ".GetAdjective] est unie et fière de son héritage impérial.",
			 "french");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Das [" + tag + ".GetAdjective]e Volk versammelt sich um den König von [" + tag + ".GetName] und die [" +
				  tag + ".GetAdjective]e Kolonien und ist vereint und stolz auf sein kaiserliches Erbe.",
			 "german");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Gromadząc się wokół Króla [" + tag + ".GetName] i [" + tag + ".GetAdjective]ich Dominiów, [" + tag +
				  ".GetAdjective] są zjednoczeni i dumni ze swojego imperialnego dziedzictwa.",
			 "polish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Сплотившись вокруг Короля [" + tag + ".GetName] и [" + tag + ".GetAdjective]их Доминионов, [" + tag +
				  ".GetAdjective]ий народ объединяется и гордится своим имперским наследием.",
			 "russian");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Reunida en torno al Rey de [" + tag + ".GetName] y las tierras [" + tag + ".GetAdjective]s, la nación [" +
				  tag + ".GetAdjective] está unida y orgullosa de su legado imperial.",
			 "spanish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "[" + tag + ".GetName]の国王と[" + tag + ".GetAdjective]の領土の周りに結集し、[" + tag +
				  ".GetAdjective]人は団結し、帝国の遺産を誇りに思っています",
			 "japanese");
	}
	else
	{
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Rallying around the Queen of [" + tag + ".GetName] and the [" + tag + ".GetAdjective] Dominions, the [" +
				  tag + ".GetAdjective] people stand united and proud of their imperial legacy.",
			 "english");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Reunindo-se em torno da Rainha da [" + tag + ".GetName] e dos Domínios [" + tag +
				  ".GetAdjective], o povo [" + tag + ".GetAdjective] se mantém unido e orgulhoso de seu legado imperial.",
			 "braz_por");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Rassemblant autour de la Reine de [" + tag + ".GetName] et des colonies [" + tag +
				  ".GetAdjective]s, la nation [" + tag + ".GetAdjective] est unie et fière de son héritage impérial.",
			 "french");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Das [" + tag + ".GetAdjective]e Volk versammelt sich um die Königin von [" + tag + ".GetName] und die [" +
				  tag + ".GetAdjective]e Kolonien und ist vereint und stolz auf sein kaiserliches Erbe.",
			 "german");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Gromadząc się wokół Królowej [" + tag + ".GetName] i [" + tag + ".GetAdjective]ich Dominiów, [" + tag +
				  ".GetAdjective] są zjednoczeni i dumni ze swojego imperialnego dziedzictwa.",
			 "polish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Сплотившись вокруг Королевы [" + tag + ".GetName] и [" + tag + ".GetAdjective]их Доминионов, [" + tag +
				  ".GetAdjective]ий народ объединяется и гордится своим имперским наследием.",
			 "russian");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "Reunida en torno a la Reina de [" + tag + ".GetName] y las tierras [" + tag +
				  ".GetAdjective]s, la nación [" + tag + ".GetAdjective] está unida y orgullosa de su legado imperial.",
			 "spanish");
		hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
			 "[" + tag + ".GetName]の女王と[" + tag + ".GetAdjective]の領土の周りに結集し、[" + tag +
				  ".GetAdjective]人は団結し、帝国の遺産を誇りに思っています",
			 "japanese");
	}

	if (!female)
	{
		if (const auto monarchPortraits = graphicsMapper.getMaleMonarchPortraits(primaryCulture, primaryCultureGroup);
			 !monarchPortraits.empty())
		{
			monarchIdeaTexture = monarchPortraits.at(
				 std::uniform_int_distribution<int>{0, static_cast<int>(monarchPortraits.size() - 1)}(generator));
		}
	}
	else
	{
		if (const auto monarchPortraits = graphicsMapper.getFemaleMonarchPortraits(primaryCulture, primaryCultureGroup);
			 !monarchPortraits.empty())
		{
			monarchIdeaTexture = monarchPortraits.at(
				 std::uniform_int_distribution<int>{0, static_cast<int>(monarchPortraits.size() - 1)}(generator));
		}
	}

	ideas.emplace(tag + "_monarch");
}


void HoI4::Country::convertRelations(const Mappers::CountryMapper& countryMap,
	 const Vic2::Country& sourceCountry,
	 const date& startDate)
{
	auto srcRelations = sourceCountry.getRelations();
	for (const auto& srcRelation: srcRelations)
	{
		auto HoI4Tag = countryMap.getHoI4Tag(srcRelation.first);
		if (HoI4Tag)
		{
			HoI4::Relations newRelation(*HoI4Tag, srcRelation.second, startDate);
			relations.insert(std::make_pair(*HoI4Tag, std::move(newRelation)));
		}
	}
}


void HoI4::Country::convertStrategies(const Mappers::CountryMapper& countryMap,
	 const Vic2::Country& sourceCountry,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const States& states,
	 const Mappers::ProvinceMapper& provinceMapper)
{
	for (const auto& [vic2Tag, data]: sourceCountry.getAI().getConsolidatedStrategies())
	{
		if (const auto& HoI4Tag = countryMap.getHoI4Tag(vic2Tag); HoI4Tag && countries.contains(*HoI4Tag))
		{
			if (HoI4Tag == tag)
			{
				continue;
			}
			HoI4::AIStrategy newStrategy("conquer", *HoI4Tag, data, states, provinceMapper);
			conquerStrategies.push_back(newStrategy);
		}
	}
	std::sort(conquerStrategies.begin(),
		 conquerStrategies.end(),
		 [](const HoI4::AIStrategy& a, const HoI4::AIStrategy& b) {
			 return a.getValue() > b.getValue();
		 });

	for (const auto& srcStrategy: sourceCountry.getAI().getStrategies())
	{
		if (const auto& HoI4Tag = countryMap.getHoI4Tag(srcStrategy.getID()); HoI4Tag && countries.contains(*HoI4Tag))
		{
			HoI4::AIStrategy newStrategy(srcStrategy, *HoI4Tag);
			aiStrategies.push_back(newStrategy);
		}
	}
}


void HoI4::Country::convertWars(const Vic2::Country& theSourceCountry,
	 const std::set<std::string>& independentCountries,
	 const Mappers::CountryMapper& countryMap,
	 const Mappers::CasusBellis& casusBellis,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const std::map<int, int>& provinceToStateIDMap)
{
	for (const auto& sourceWar: theSourceCountry.getWars())
	{
		War theWar(sourceWar, independentCountries, countryMap, casusBellis, provinceMapper, provinceToStateIDMap);
		wars.push_back(theWar);
	}
}


void HoI4::Country::addTag(const std::string& tag_, Names& names, Localisation& hoi4Localisations)
{
	tag = tag_;
	determineFilename();
	initIdeas(names, hoi4Localisations);
}


void HoI4::Country::addMonarchIdea(const Country& owner)
{
	if (owner.hasMonarchIdea())
	{
		ideas.insert(owner.tag + "_monarch");
	}
}


void HoI4::Country::determineCapitalFromVic2(const Mappers::ProvinceMapper& theProvinceMapper,
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
		if (name_)
		{
			Log(LogLevel::Warning) << "Could not properly set capital for " << tag << " - " << *name_;
		}
		else
		{
			Log(LogLevel::Warning) << "Could not properly set capital for " << tag;
		}
	}
}


void HoI4::Country::determineBestCapital(const std::map<int, State>& allStates)
{
	auto success = attemptToPutCapitalInNonWastelandOwned(allStates);
	if (!success)
	{
		success = attemptToPutCapitalInAnyOwned(allStates);
	}
	if (!success)
	{
		success = attemptToPutCapitalInAnyNonWastelandCored(allStates);
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


bool HoI4::Country::attemptToPutCapitalInPreferredNonWastelandOwned(const Mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); !mapping.empty())
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find(mapping[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if ((state.getOwner() == tag) && !state.isImpassable())
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = mapping[0];
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


bool HoI4::Country::attemptToPutCapitalInPreferredWastelandOwned(const Mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); !mapping.empty())
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find(mapping[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if (state.getOwner() == tag)
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = mapping[0];
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


bool HoI4::Country::attemptToPutCapitalInPreferredNonWastelandCored(const Mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); !mapping.empty())
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find(mapping[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if ((state.getCores().contains(tag) || state.getClaims().contains(tag)) && !state.isImpassable())
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = mapping[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyNonWastelandCored(const std::map<int, State>& allStates)
{
	for (auto coredStateNum: coreStates)
	{
		if (auto stateAndNum = allStates.find(coredStateNum); stateAndNum != allStates.end())
		{
			auto state = stateAndNum->second;
			if ((state.getCores().contains(tag) || state.getClaims().contains(tag)) && !state.isImpassable())
			{
				capitalState = coredStateNum;
				capitalProvince = *state.getProvinces().begin();
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInPreferredWastelandCored(const Mappers::ProvinceMapper& theProvinceMapper,
	 const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, State>& allStates)
{
	if (auto mapping = theProvinceMapper.getVic2ToHoI4ProvinceMapping(oldCapital); !mapping.empty())
	{
		if (const auto capitalStateMapping = provinceToStateIDMap.find(mapping[0]);
			 capitalStateMapping != provinceToStateIDMap.end())
		{
			const auto& state = allStates.find(capitalStateMapping->second)->second;
			if (state.getCores().contains(tag) || state.getClaims().contains(tag))
			{
				capitalState = capitalStateMapping->second;
				capitalProvince = mapping[0];
				return true;
			}
		}
	}

	return false;
}


bool HoI4::Country::attemptToPutCapitalInAnyCored(const std::map<int, State>& allStates)
{
	for (auto coredStateNum: coreStates)
	{
		if (auto state = allStates.find(coredStateNum); state != allStates.end())
		{
			if (state->second.getCores().contains(tag) || state->second.getClaims().contains(tag))
			{
				capitalState = coredStateNum;
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
		return {};
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
	 const Mappers::GovernmentMapper& governmentMap,
	 Localisation& hoi4Localisations,
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
	if (hasRulingDynasty())
	{
		hoi4Localisations.addRulingHouseLocalisations(tag + "_" + governmentIdeology + "_party", *lastDynasty);
	}
}


void HoI4::Country::createLeader(Names& names,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Character::Factory& characterFactory,
	 Localisation& localisation)
{
	for (const auto& character: characters_)
	{
		const auto& countryLeaderData = character.getCountryLeaderData();
		if (countryLeaderData.has_value() && countryLeaderData->getIdeology() == leaderIdeology)
		{
			return;
		}
	}

	characters_.push_back(characterFactory.createNewCountryLeader(tag,
		 nextMonarch,
		 primaryCulture,
		 primaryCultureGroup,
		 governmentIdeology,
		 leaderIdeology,
		 names,
		 graphicsMapper,
		 localisation,
		 generator));
}


void HoI4::Country::convertIdeologySupport(const std::set<std::string>& majorIdeologies,
	 const Mappers::IdeologyMapper& partyMapper)
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
		auto ideology = partyMapper.getSupportedIdeology(governmentIdeology, upperHouseIdeology.first, majorIdeologies);
		auto supportItr = ideologySupport.find(ideology);
		if (supportItr == ideologySupport.end())
		{
			ideologySupport.insert(make_pair(ideology, 0));
			supportItr = ideologySupport.find(ideology);
		}
		supportItr->second += static_cast<int>(upperHouseIdeology.second * 100);
	}

	auto remainingSupport = 100;
	for (auto& ideology: ideologySupport)
	{
		if (puppetMaster && ideology.first == getLeaderIdeology()) // Add support for puppetmaster's ideology
		{
			if (ideology.second > 20)
			{
				ideology.second -= 20;
				ideologySupport.find(getPuppetMaster()->getLeaderIdeology())->second += 20;
			}
			else
			{
				ideologySupport.find(getPuppetMaster()->getLeaderIdeology())->second += ideology.second;
				ideology.second = 0;
			}
		}
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
	 const Maps::ProvinceDefinitions& provinceDefinitions,
	 const Mappers::ProvinceMapper& provinceMapper)
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

	if (backupNavalLocation != 0)
	{
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
	}

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
	int amount = 0;
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
						amount += unitInfo.getSize();
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
	amount /= 2;

	if (theTechnologies->hasTechnology("basic_small_airframe"))
	{
		equipment_stockpile_.emplace_back(tag,
			 "small_plane_airframe_1",
			 "Basic Fighter",
			 R"(has_dlc = "By Blood Alone")",
			 amount);
		equipment_stockpile_.emplace_back(tag,
			 "small_plane_cas_airframe_1",
			 "Basic CAS",
			 R"(has_dlc = "By Blood Alone")",
			 amount);
	}
	else
	{
		equipment_stockpile_.emplace_back(tag,
			 "small_plane_airframe_0",
			 "Interwar Fighter",
			 R"(has_dlc = "By Blood Alone")",
			 amount);
		equipment_stockpile_.emplace_back(tag,
			 "small_plane_cas_airframe_0",
			 "Interwar CAS",
			 R"(has_dlc = "By Blood Alone")",
			 amount);
	}
	equipment_stockpile_.emplace_back(tag,
		 "fighter_equipment_0",
		 std::nullopt,
		 R"(NOT = { has_dlc = "By Blood Alone" })",
		 amount);
	equipment_stockpile_.emplace_back(tag,
		 "tac_bomber_equipment_0",
		 std::nullopt,
		 R"(NOT = { has_dlc = "By Blood Alone" })",
		 amount);
}


void HoI4::Country::convertArmies(const militaryMappings& theMilitaryMappings,
	 const HoI4::States& theStates,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Configuration& theConfiguration)
{
	if (capitalProvince)
	{
		theArmy.ConvertArmies(theMilitaryMappings,
			 *capitalProvince,
			 theConfiguration.getForceMultiplier(),
			 *theTechnologies,
			 theStates,
			 provinceMapper,
			 tag);
	}
	else
	{
		theArmy.ConvertArmies(theMilitaryMappings,
			 0,
			 theConfiguration.getForceMultiplier(),
			 *theTechnologies,
			 theStates,
			 provinceMapper,
			 tag);
	}

	for (const auto& equipment: theArmy.GetLeftoverEquipment())
	{
		equipment_stockpile_.push_back(equipment);
	}

	convertStockpile();
}


float HoI4::Country::getSourceCountryGoodAmount(const std::string& goodType)
{
	if (const auto good = sourceCountryGoods.find(goodType); good != sourceCountryGoods.end())
	{
		return good->second;
	}

	return 0.0F;
}


constexpr float max_stockpile = 2000.0F;
constexpr float barrels_supply_required_for_light_armor = 1.1175F;
constexpr float artillery_supply_required_for_light_armor = 0.745F;
constexpr float canned_food_supply_required_for_light_armor = 0.755F;
constexpr float fuel_supply_required_for_light_armor = 1.49F;
constexpr float full_light_armor_supply = 2000.0F / 1.49F;
constexpr float light_armor_equipment_per_division = 60.0F;
constexpr float artillery_supply_required_for_artillery = 0.76F;
constexpr float canned_food_supply_required_for_artillery = 0.456F;
constexpr float full_artillery_supply = 2000.0F / 0.76F;
constexpr float artillery_equipment_per_division = 12.0F;
constexpr float small_arms_supply_required_for_infantry = 0.0726F;
constexpr float ammunition_supply_required_for_infantry = 0.45375F;
constexpr float canned_food_supply_required_for_infantry = 0.4235F;
constexpr float full_infantry_supply = 2000.0F / 0.45375F;
constexpr float infantry_equipment_per_division = 100.0F;
constexpr float small_arms_supply_required_for_cavalry = 0.08775F;
constexpr float ammunition_supply_required_for_cavalry = 0.43875F;
constexpr float canned_food_supply_required_for_cavalry = 0.468F;
constexpr float full_cavalry_supply = 2000.0F / 0.468F;
constexpr float cavalry_equipment_per_division = 120.0F;
void HoI4::Country::convertStockpile()
{
	const auto divisionTypesAndAmounts = theArmy.getDivisionTypesAndAmounts();

	// convert supply into light armor equipment via light_armor
	std::set<float> armorSupplyLevels{getSourceCountryGoodAmount("barrels") / barrels_supply_required_for_light_armor,
		 getSourceCountryGoodAmount("artillery") / artillery_supply_required_for_light_armor,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_light_armor,
		 getSourceCountryGoodAmount("fuel") / fuel_supply_required_for_light_armor};
	const auto armorSupply = *std::min_element(armorSupplyLevels.begin(), armorSupplyLevels.end());
	if (const auto tanks = divisionTypesAndAmounts.find("light_armor"); tanks != divisionTypesAndAmounts.end())
	{
		const auto amount = static_cast<int>(std::ceil(static_cast<float>(tanks->second) * armorSupply /
																	  full_light_armor_supply * light_armor_equipment_per_division));
		equipment_stockpile_.emplace_back(tag,
			 "gw_tank_equipment",
			 std::nullopt,
			 R"(NOT = { has_dlc = "No Step Back" })",
			 amount);
		if (theTechnologies->hasTechnology("basic_light_tank_chassis"))
		{
			equipment_stockpile_.emplace_back(tag,
				 "light_tank_chassis_1",
				 "Basic Light Tank",
				 R"(has_dlc = "No Step Back")",
				 amount);
		}
		else
		{
			equipment_stockpile_.emplace_back(tag,
				 "light_tank_chassis_0",
				 "GW Light Tank",
				 R"(has_dlc = "No Step Back")",
				 amount);
		}
	}
	sourceCountryGoods["barrels"] -= barrels_supply_required_for_light_armor * armorSupply;
	sourceCountryGoods["artillery"] -= artillery_supply_required_for_light_armor * armorSupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_light_armor * armorSupply;
	sourceCountryGoods["fuel"] -= fuel_supply_required_for_light_armor * armorSupply;

	// convert supply into artillery equipment via artillery_brigade
	std::set artillerySupplyLevels{getSourceCountryGoodAmount("artillery") / artillery_supply_required_for_artillery,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_artillery};
	const auto artillerySupply = *std::min_element(artillerySupplyLevels.begin(), artillerySupplyLevels.end());
	if (const auto artillery = divisionTypesAndAmounts.find("artillery_brigade");
		 artillery != divisionTypesAndAmounts.end())
	{
		equipment_stockpile_.emplace_back(tag,
			 "artillery_equipment_1",
			 std::nullopt,
			 std::nullopt,
			 static_cast<int>(std::ceil(static_cast<float>(artillery->second) * artillerySupply / full_artillery_supply *
												 artillery_equipment_per_division)));
	}
	sourceCountryGoods["artillery"] -= artillery_supply_required_for_artillery * artillerySupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_artillery * artillerySupply;

	// convert supply into infantry equipment via infantry
	int infantry_equipment_amount = 0;
	std::set infantrySupplyLevels{getSourceCountryGoodAmount("small_arms") / small_arms_supply_required_for_infantry,
		 getSourceCountryGoodAmount("ammunition") / ammunition_supply_required_for_infantry,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_infantry};
	const auto infantrySupply = *std::min_element(infantrySupplyLevels.begin(), infantrySupplyLevels.end());
	if (const auto tanks = divisionTypesAndAmounts.find("infantry"); tanks != divisionTypesAndAmounts.end())
	{
		infantry_equipment_amount += static_cast<int>(std::ceil(
			 static_cast<float>(tanks->second) * infantrySupply / full_infantry_supply * infantry_equipment_per_division));
	}
	sourceCountryGoods["small_arms"] -= small_arms_supply_required_for_infantry * infantrySupply;
	sourceCountryGoods["ammunition"] -= ammunition_supply_required_for_infantry * infantrySupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_infantry * infantrySupply;

	// convert supply into infantry equipment via cavalry
	std::set cavalrySupplyLevels{getSourceCountryGoodAmount("small_arms") / small_arms_supply_required_for_cavalry,
		 getSourceCountryGoodAmount("ammunition") / ammunition_supply_required_for_cavalry,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_cavalry};
	const auto cavalrySupply = *std::min_element(cavalrySupplyLevels.begin(), cavalrySupplyLevels.end());
	if (const auto tanks = divisionTypesAndAmounts.find("cavalry"); tanks != divisionTypesAndAmounts.end())
	{
		infantry_equipment_amount += static_cast<int>(std::ceil(
			 static_cast<float>(tanks->second) * cavalrySupply / full_cavalry_supply * cavalry_equipment_per_division));
	}
	sourceCountryGoods["small_arms"] -= small_arms_supply_required_for_cavalry * cavalrySupply;
	sourceCountryGoods["ammunition"] -= ammunition_supply_required_for_cavalry * cavalrySupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_cavalry * cavalrySupply;
	if (infantry_equipment_amount > 0)
	{
		equipment_stockpile_.emplace_back(tag,
			 "infantry_equipment_0",
			 std::nullopt,
			 std::nullopt,
			 infantry_equipment_amount);
	}
}


void HoI4::Country::addState(const State& state)
{
	states.insert(state.getID());
	nationalPopulation += state.getPopulation();
	for (const auto province: state.getProvinces())
	{
		provinces.insert(province);
	}
}


void HoI4::Country::removeState(const State& state)
{
	states.erase(state.getID());

	for (const auto province: state.getProvinces())
	{
		provinces.erase(province);
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


std::optional<date> HoI4::Country::getTruceUntil(const std::string& withWhom) const
{
	if (const auto& relations = getRelations(withWhom); relations && relations->getTruceDuration())
	{
		return relations->getTruceUntil();
	}
	else
	{
		return std::nullopt;
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


void HoI4::Country::addEmptyFocusTree()
{
	if (!nationalFocus)
	{
		HoI4FocusTree emptyNationalFocus(*this);
		emptyNationalFocus.makeEmpty();
		nationalFocus = emptyNationalFocus.makeCustomizedCopy(*this);
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


void HoI4::Country::transferPuppets(const std::set<std::shared_ptr<Country>>& transferringPuppets,
	 std::shared_ptr<HoI4::Country> dominion,
	 const Regions& theRegions)
{
	for (const auto& puppet: transferringPuppets)
	{
		puppets.erase(puppet->getTag());
		dominion->addPuppet(puppet, theRegions);
	}
}


void HoI4::Country::addPuppetsIntegrationTree(HoI4::Localisation& hoi4Localisations, bool debug)
{
	nationalFocus->addIntegratePuppetsBranch(tag, puppets, hoi4Localisations, debug);
}


void HoI4::Country::addAdjustedBranch(const std::shared_ptr<HoI4::AdjustedBranch>& theBranch,
	 const std::string& originalTag,
	 HoI4::OnActions& onActions)
{
	if (nationalFocus)
	{
		nationalFocus->addBranch(theBranch->getFocusTree().getFocuses(), onActions);
	}

	addGlobalEventTarget(theBranch->getName() + "_" + originalTag);

	HoI4::Character::Factory characterFactory;
	for (auto character: theBranch->getModifiableCharacters() | std::views::values)
	{
		const auto& portrait_location =
			 armyPortraits[std::uniform_int_distribution<int>{0, static_cast<int>(armyPortraits.size() - 1)}(generator)];
		characterFactory.customizeCharacterPortraits(character, portrait_location);

		addCharacter(character);
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
	if (!theNavies)
	{
		return navalStrength;
	}

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


bool HoI4::Country::hasMonarchIdea() const
{
	return (oldGovernment == "prussian_constitutionalism" || oldGovernment == "hms_government") &&
			 (governmentIdeology != "absolutist") && (leaderIdeology != "absolute_monarchy_neutral");
}


float HoI4::Country::GetResourcesMultiplier() const
{
	if (!civilized)
	{
		return 0.0F;
	}
	if (unrecognizedNation)
	{
		return 0.0F;
	}

	float top_industry_technologies = 0.0F;
	if (oldTechnologiesAndInventions.contains("electrical_power_generation"))
	{
		++top_industry_technologies;
	}
	if (oldTechnologiesAndInventions.contains("shift_work"))
	{
		++top_industry_technologies;
	}
	if (oldTechnologiesAndInventions.contains("electric_furnace"))
	{
		++top_industry_technologies;
	}
	if (oldTechnologiesAndInventions.contains("limited_access_roads"))
	{
		++top_industry_technologies;
	}
	if (oldTechnologiesAndInventions.contains("synthetic_polymers"))
	{
		++top_industry_technologies;
	}

	const float a = 0.025F * top_industry_technologies * top_industry_technologies;
	const float b = 0.075F * top_industry_technologies;
	return a + b;
}


const bool HoI4::Country::isEligibleEnemy(std::string target) const
{
	auto allAllies = allies;
	if (faction)
	{
		allAllies.insert(faction->getLeader()->getAllies().begin(), faction->getLeader()->getAllies().end());
		allAllies.insert(faction->getLeader()->getTag());
	}
	std::string puppetMasterTag;
	if (puppetMaster)
	{
		puppetMasterTag = puppetMaster->getTag();
	}

	return !allAllies.contains(target) && !puppets.contains(target) && target != puppetMasterTag;
}

std::optional<std::string> HoI4::Country::getDominionTag(const std::string& region)
{
	if (generatedDominions.find(region) == generatedDominions.end())
	{
		return std::nullopt;
	}
	return generatedDominions.at(region);
}


std::vector<std::set<int>> HoI4::Country::getDominionAreas(const std::unique_ptr<Maps::MapData>& theMapData,
	 const std::map<int, HoI4::State>& allStates,
	 const std::map<int, int>& provinceToStateIdMap)
{
	std::vector<std::set<int>> dominionAreas;
	std::set<int> area;

	// Provinces with land connection to capital take the 0 index in dominionAreas vector
	addProvincesToArea(*capitalProvince, area, theMapData, allStates, provinceToStateIdMap);
	dominionAreas.push_back(area);

	// Then cycle through the rest and make province clusters for potential transfer to dominions
	for (const auto& stateId: states)
	{
		const auto& state = allStates.find(stateId);
		if (state == allStates.end())
		{
			continue;
		}
		area.clear();

		// Check every province in state to ensure that island provinces are added properly
		for (const auto& province: state->second.getProvinces())
		{
			if (isProvinceInDominionArea(province, dominionAreas))
			{
				continue;
			}
			addProvincesToArea(province, area, theMapData, allStates, provinceToStateIdMap);
		}
		dominionAreas.push_back(area);
	}
	return dominionAreas;
}


void HoI4::Country::addProvincesToArea(int province,
	 std::set<int>& area,
	 const std::unique_ptr<Maps::MapData>& theMapData,
	 const std::map<int, HoI4::State>& allStates,
	 const std::map<int, int>& provinceToStateIdMap)
{
	// If the province is in area, then it and all its neighbors have been processed and added to area
	if (area.contains(province))
	{
		return;
	}
	auto provinceToStateIdMapping = provinceToStateIdMap.find(province);
	if (provinceToStateIdMapping == provinceToStateIdMap.end())
	{
		return;
	}
	const auto& stateId = provinceToStateIdMapping->second;
	// Provinces owned by other countries break the contiguousness
	if (const auto& state = allStates.find(stateId); state->second.getOwner() != tag)
	{
		return;
	}
	area.insert(province);

	for (const auto& neighbor: theMapData->GetNeighbors(province))
	{
		addProvincesToArea(neighbor, area, theMapData, allStates, provinceToStateIdMap);
	}
}


bool HoI4::Country::isProvinceInDominionArea(int province, const std::vector<std::set<int>>& dominionAreas)
{
	return std::ranges::any_of(dominionAreas, [province](const std::set<int>& area) {
		return area.contains(province);
	});
}


void HoI4::Country::AddPlaneDesigns(const PossiblePlaneDesigns& possible_designs)
{
	plane_designs_ = std::make_unique<PlaneDesigns>(possible_designs, *theTechnologies);
}


void HoI4::Country::addTankDesigns(const PossibleTankDesigns& possibleDesigns)
{
	tankDesigns = std::make_unique<TankDesigns>(possibleDesigns, *theTechnologies);
}


std::optional<HoI4::Navies> HoI4::Country::getNavies() const
{
	if (theNavies)
	{
		return std::make_optional(*theNavies);
	}
	else
	{
		return std::nullopt;
	}
}


void HoI4::Country::addPuppet(const std::shared_ptr<Country> puppet, const Regions& theRegions)
{
	const auto& masterRegion = theRegions.getRegion(*capitalProvince);
	const auto& puppetRegion = theRegions.getRegion(*puppet->getCapitalProvince());

	if (!masterRegion || !puppetRegion)
	{
		return;
	}

	std::string autonomyLevel = "autonomy_dominion";
	if (theRegions.isRegionBlocked(*puppetRegion, *masterRegion))
	{
		autonomyLevel = "autonomy_puppet";
	}
	else if (const auto& regionLevel = theRegions.getRegionLevel(*puppetRegion); regionLevel)
	{
		autonomyLevel = *regionLevel;
	}

	puppets[puppet->getTag()] = autonomyLevel;
}