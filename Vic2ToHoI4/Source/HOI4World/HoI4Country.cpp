#include "HoI4Country.h"
#include "Diplomacy/HoI4War.h"
#include "HoI4Localisation.h"
#include "HoI4World.h"
#include "Leaders/CountryLeaderFactory.h"
#include "Log.h"
#include "Mappers/Country/CountryMapper.h"
#include "Mappers/Government/GovernmentMapper.h"
#include "Mappers/Graphics/GraphicsMapper.h"
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
#include <cmath>



HoI4::Country::Country(std::string tag,
	 const Vic2::Country& sourceCountry,
	 Names& names,
	 Mappers::GraphicsMapper& graphicsMapper,
	 const Mappers::CountryMapper& countryMap,
	 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
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

	auto possibleGraphicalCulture = graphicsMapper.getGraphicalCulture(primaryCultureGroup);
	if (possibleGraphicalCulture)
	{
		graphicalCulture = *possibleGraphicalCulture;
	}
	auto possibleGraphicalCulture2d = graphicsMapper.get2dGraphicalCulture(primaryCultureGroup);
	if (possibleGraphicalCulture2d)
	{
		graphicalCulture2d = *possibleGraphicalCulture2d;
	}
	armyPortraits = graphicsMapper.getArmyPortraits(primaryCultureGroup);
	navyPortraits = graphicsMapper.getNavyPortraits(primaryCultureGroup);
	communistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "communism");
	democraticAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "democratic");
	neutralityAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "neutrality");
	absolutistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "absolutist");
	radicalAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "radical");
	fascistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "fascism");

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
	convertLeaders(sourceCountry);
	convertRelations(countryMap, sourceCountry);
	convertStrategies(countryMap, sourceCountry);
	atWar = sourceCountry.isAtWar();
	convertWars(sourceCountry, countryMap);

	employedWorkers = sourceCountry.getEmployedWorkers();

	oldArmies = sourceCountry.getArmies();
	theArmy.addSourceArmies(oldArmies);
	shipNames = sourceCountry.getAllShipNames();

	sourceCountryGoods = sourceCountry.getGoodsStockpile();

	createOperatives(graphicsMapper, names);
}


HoI4::Country::Country(const std::string& tag_,
	 const Country& owner,
	 const std::string& region_,
	 const Regions& regions,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names,
	 Localisation& hoi4Localisations):
	 tag(tag_),
	 primaryCulture(owner.primaryCulture), primaryCultureGroup(owner.primaryCultureGroup), civilized(owner.civilized),
	 rulingParty(owner.rulingParty), parties(owner.parties), upperHouseComposition(owner.upperHouseComposition),
	 lastElection(owner.lastElection), color(owner.color), graphicalCulture(owner.graphicalCulture),
	 graphicalCulture2d(owner.graphicalCulture2d), warSupport(owner.warSupport),
	 oldTechnologiesAndInventions(owner.oldTechnologiesAndInventions), atWar(owner.atWar), shipNames(owner.shipNames),
	 generatedDominion(true), region(region_), puppetMaster(owner.getTag()), puppetMasterOldTag(owner.getOldTag()),
	 governmentIdeology(owner.getGovernmentIdeology()), leaderIdeology(owner.getLeaderIdeology()), oldCapital(-1)
{
	if (const auto& regionName = regions.getRegionName(region); regionName)
	{
		if (const auto& ownerAdjective = owner.adjective; ownerAdjective)
		{
			name = *ownerAdjective + " " + *regionName;
		}
		else
		{
			name = *regionName;
		}
	}

	if (const auto& regionAdjective = regions.getRegionAdjective(region); regionAdjective)
	{
		adjective = *regionAdjective;
	}

	determineFilename();

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

	armyPortraits = graphicsMapper.getArmyPortraits(primaryCultureGroup);
	navyPortraits = graphicsMapper.getNavyPortraits(primaryCultureGroup);
	communistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "communism");
	democraticAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "democratic");
	neutralityAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "neutrality");
	absolutistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "absolutist");
	radicalAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "radical");
	fascistAdvisorPortrait = graphicsMapper.getIdeologyMinisterPortrait(primaryCultureGroup, "fascism");

	initIdeas(names, hoi4Localisations);
	if (owner.hasMonarchIdea())
	{
		ideas.insert(owner.tag + "_monarch");
	}

	createOperatives(graphicsMapper, names);

	convertLaws();
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
	 const Mappers::GovernmentMapper& governmentMap,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 Mappers::GraphicsMapper& graphicsMapper,
	 Names& names,
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
	convertMonarchIdea(graphicsMapper, names, hoi4Localisations);
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


void HoI4::Country::createOperatives(const Mappers::GraphicsMapper& graphicsMapper, Names& names)
{
	for (const auto& operativePortrait: graphicsMapper.getFemaleOperativePortraits(primaryCultureGroup))
	{
		const auto firstName = names.getFemaleName(primaryCulture);
		if (!firstName)
		{
			break;
		}

		auto surname = names.getFemaleSurname(primaryCulture);
		if (!surname)
		{
			surname = names.getSurname(primaryCulture);
		}
		if (!surname)
		{
			break;
		}

		const std::string name = *firstName + " " + *surname;
		operatives_.push_back(Operative(name, operativePortrait, /*female=*/ true, tag));
	}

	for (const auto& operativePortrait: graphicsMapper.getMaleOperativePortraits(primaryCultureGroup))
	{
		const auto firstName = names.getMaleName(primaryCulture);
		if (!firstName)
		{
			break;
		}

		auto surname = names.getSurname(primaryCulture);
		if (!surname)
		{
			break;
		}

		const std::string name = *firstName + " " + *surname;
		operatives_.push_back(Operative(name, operativePortrait, /*female=*/false, tag));
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


void HoI4::Country::convertLeaders(const Vic2::Country& sourceCountry)
{
	auto srcLeaders = sourceCountry.getLeaders();
	for (auto srcLeader: srcLeaders)
	{
		if (srcLeader.getType() == "land")
		{
			General newLeader(srcLeader);
			generals.push_back(newLeader);
		}
		else if (srcLeader.getType() == "sea")
		{
			Admiral newLeader(srcLeader);
			admirals.push_back(newLeader);
		}
	}
}


void HoI4::Country::convertMonarchIdea(const Mappers::GraphicsMapper& graphicsMapper,
	 Names& names,
	 Localisation& hoi4Localisations)
{
	if (!hasMonarchIdea())
	{
		return;
	}

	std::optional<std::string> firstName;
	std::optional<std::string> surname = lastDynasty;

	bool female = false; // todo(#897): Add chance of female monarchs
	if (female)
	{
		firstName = names.getFemaleName(primaryCulture);
		auto femaleSurname = names.getFemaleSurname(primaryCulture);
		if (!firstName)
		{
			firstName = names.getMaleName(primaryCulture);
			if (!surname)
			{
				surname = names.getSurname(primaryCulture);
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
				surname = names.getSurname(primaryCulture);
			}
		}
	}
	else
	{
		firstName = names.getMaleName(primaryCulture);
		const auto newSurname = names.getSurname(primaryCulture);

		if (!firstName)
		{
			firstName = names.getFemaleName(primaryCulture);
			auto femaleSurname = names.getFemaleSurname(primaryCulture);
			if (!newSurname && femaleSurname)
			{
				surname = femaleSurname;
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
	}

	if (name && adjective)
	{
		if (!female)
		{
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Rallying around the King of " + *name + " and the " + *adjective + " Dominions, the " + *adjective +
					  " people stand united and proud of their imperial legacy.",
				 "english");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Reunindo-se em torno do Rei da " + *name + " e dos Domínios " + *adjective + ", o povo " + *adjective +
					  " se mantém unido e orgulhoso de seu legado imperial.",
				 "braz_por");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Rassemblant autour du Roi de " + *name + " et des colonies " + *adjective + "s, la nation " + *adjective +
					  " est unie et fière de son héritage impérial.",
				 "french");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Das " + *adjective + "e Volk versammelt sich um den König von " + *name + " und die " + *adjective +
					  "e Kolonien und ist vereint und stolz auf sein kaiserliches Erbe.",
				 "german");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Gromadząc się wokół Króla " + *name + " i " + *adjective + "ich Dominiów, " + *adjective +
					  " są zjednoczeni i dumni ze swojego imperialnego dziedzictwa.",
				 "polish");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Сплотившись вокруг Короля " + *name + " и " + *adjective + "их Доминионов, " + *adjective +
					  "ий народ объединяется и гордится своим имперским наследием.",
				 "russian");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Reunida en torno al Rey de " + *name + " y las tierras " + *adjective + "s, la nación " + *adjective +
					  " está unida y orgullosa de su legado imperial.",
				 "spanish");
		}
		else
		{
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Rallying around the Queen of " + *name + " and the " + *adjective + " Dominions, the " + *adjective +
					  " people stand united and proud of their imperial legacy.",
				 "english");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Reunindo-se em torno da Rainha da " + *name + " e dos Domínios " + *adjective + ", o povo " + *adjective +
					  " se mantém unido e orgulhoso de seu legado imperial.",
				 "braz_por");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Rassemblant autour de la Reine de " + *name + " et des colonies " + *adjective + "s, la nation " +
					  *adjective + " est unie et fière de son héritage impérial.",
				 "french");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Das " + *adjective + "e Volk versammelt sich um die Königin von " + *name + " und die " + *adjective +
					  "e Kolonien und ist vereint und stolz auf sein kaiserliches Erbe.",
				 "german");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Gromadząc się wokół Królowej " + *name + " i " + *adjective + "ich Dominiów, " + *adjective +
					  " są zjednoczeni i dumni ze swojego imperialnego dziedzictwa.",
				 "polish");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Сплотившись вокруг Королевы " + *name + " и " + *adjective + "их Доминионов, " + *adjective +
					  "ий народ объединяется и гордится своим имперским наследием.",
				 "russian");
			hoi4Localisations.addIdeaLocalisation(tag + "_monarch_desc",
				 "Reunida en torno a la Reina de " + *name + " y las tierras " + *adjective + "s, la nación " + *adjective +
					  " está unida y orgullosa de su legado imperial.",
				 "spanish");
		}
	}

	if (!female)
	{
		const auto monarchPortraits = graphicsMapper.getMaleMonarchPortraits(primaryCultureGroup);
		if (!monarchPortraits.empty())
		{
			monarchIdeaTexture = monarchPortraits.at(
				 std::uniform_int_distribution<int>{0, static_cast<int>(monarchPortraits.size() - 1)}(generator));
		}
	}
	else
	{
		const auto monarchPortraits = graphicsMapper.getFemaleMonarchPortraits(primaryCultureGroup);
		if (!monarchPortraits.empty())
		{
			monarchIdeaTexture = monarchPortraits.at(
				 std::uniform_int_distribution<int>{0, static_cast<int>(monarchPortraits.size() - 1)}(generator));
		}
	}

	ideas.emplace(tag + "_monarch");
}


void HoI4::Country::convertRelations(const Mappers::CountryMapper& countryMap, const Vic2::Country& sourceCountry)
{
	auto srcRelations = sourceCountry.getRelations();
	for (const auto& srcRelation: srcRelations)
	{
		auto HoI4Tag = countryMap.getHoI4Tag(srcRelation.first);
		if (HoI4Tag)
		{
			HoI4::Relations newRelation(*HoI4Tag, srcRelation.second);
			relations.insert(std::make_pair(*HoI4Tag, std::move(newRelation)));
		}
	}
}


void HoI4::Country::convertStrategies(const Mappers::CountryMapper& countryMap, const Vic2::Country& sourceCountry)
{
	for (const auto& [vic2Tag, strategy]: sourceCountry.getAI().getConsolidatedStrategies())
	{
		if (const auto& HoI4Tag = countryMap.getHoI4Tag(vic2Tag); HoI4Tag)
		{
			if (HoI4Tag == tag)
			{
				continue;
			}
			HoI4::AIStrategy newStrategy("conquer", *HoI4Tag, strategy);
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
		if (const auto& HoI4Tag = countryMap.getHoI4Tag(srcStrategy.getID()); HoI4Tag)
		{
			HoI4::AIStrategy newStrategy(srcStrategy, *HoI4Tag);
			aiStrategies.push_back(newStrategy);
		}
	}
}


void HoI4::Country::convertWars(const Vic2::Country& theSourceCountry, const Mappers::CountryMapper& countryMap)
{
	for (const auto& sourceWar: theSourceCountry.getWars())
	{
		War theWar(sourceWar, countryMap);
		wars.push_back(theWar);
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
		Log(LogLevel::Warning) << "Could not properly set capital for " << tag;
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


void HoI4::Country::createLeader(Names& names, Mappers::GraphicsMapper& graphicsMapper)
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
		 graphicsMapper));
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
	 const Mappers::ProvinceMapper& provinceMapper,
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
		equipmentStockpile["gw_tank_equipment"] +=
			 static_cast<int>(std::ceil(static_cast<float>(tanks->second) * armorSupply / full_light_armor_supply *
												 light_armor_equipment_per_division));
	}
	sourceCountryGoods["barrels"] -= barrels_supply_required_for_light_armor * armorSupply;
	sourceCountryGoods["artillery"] -= artillery_supply_required_for_light_armor * armorSupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_light_armor * armorSupply;
	sourceCountryGoods["fuel"] -= fuel_supply_required_for_light_armor * armorSupply;

	// convert supply into artillery equipment via artillery_brigade
	std::set<float> artillerySupplyLevels{
		 getSourceCountryGoodAmount("artillery") / artillery_supply_required_for_artillery,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_artillery};
	const auto artillerySupply = *std::min_element(artillerySupplyLevels.begin(), artillerySupplyLevels.end());
	if (const auto artillery = divisionTypesAndAmounts.find("artillery_brigade");
		 artillery != divisionTypesAndAmounts.end())
	{
		equipmentStockpile["artillery_equipment_1"] +=
			 static_cast<int>(std::ceil(static_cast<float>(artillery->second) * artillerySupply / full_artillery_supply *
												 artillery_equipment_per_division));
	}
	sourceCountryGoods["artillery"] -= artillery_supply_required_for_artillery * artillerySupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_artillery * artillerySupply;

	// convert supply into infantry equipment via infantry
	std::set<float> infantrySupplyLevels{
		 getSourceCountryGoodAmount("small_arms") / small_arms_supply_required_for_infantry,
		 getSourceCountryGoodAmount("ammunition") / ammunition_supply_required_for_infantry,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_infantry};
	const auto infantrySupply = *std::min_element(infantrySupplyLevels.begin(), infantrySupplyLevels.end());
	if (const auto tanks = divisionTypesAndAmounts.find("infantry"); tanks != divisionTypesAndAmounts.end())
	{
		equipmentStockpile["infantry_equipment_0"] += static_cast<int>(std::ceil(
			 static_cast<float>(tanks->second) * infantrySupply / full_infantry_supply * infantry_equipment_per_division));
	}
	sourceCountryGoods["small_arms"] -= small_arms_supply_required_for_infantry * infantrySupply;
	sourceCountryGoods["ammunition"] -= ammunition_supply_required_for_infantry * infantrySupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_infantry * infantrySupply;

	// convert supply into infantry equipment via cavalry
	std::set<float> cavalrySupplyLevels{
		 getSourceCountryGoodAmount("small_arms") / small_arms_supply_required_for_cavalry,
		 getSourceCountryGoodAmount("ammunition") / ammunition_supply_required_for_cavalry,
		 getSourceCountryGoodAmount("canned_food") / canned_food_supply_required_for_cavalry};
	const auto cavalrySupply = *std::min_element(cavalrySupplyLevels.begin(), cavalrySupplyLevels.end());
	if (const auto tanks = divisionTypesAndAmounts.find("cavalry"); tanks != divisionTypesAndAmounts.end())
	{
		equipmentStockpile["infantry_equipment_0"] += static_cast<int>(std::ceil(
			 static_cast<float>(tanks->second) * cavalrySupply / full_cavalry_supply * cavalry_equipment_per_division));
	}
	sourceCountryGoods["small_arms"] -= small_arms_supply_required_for_cavalry * cavalrySupply;
	sourceCountryGoods["ammunition"] -= ammunition_supply_required_for_cavalry * cavalrySupply;
	sourceCountryGoods["canned_food"] -= canned_food_supply_required_for_cavalry * cavalrySupply;
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


void HoI4::Country::transferPuppets(const std::set<std::string>& transferingPuppets, std::shared_ptr<HoI4::Country> dominion)
{
	for (const auto& puppet: transferingPuppets)
	{
		puppets.erase(puppet);
		spherelings.erase(puppet);
		dominion->addPuppet(puppet);
	}
}


void HoI4::Country::addPuppetsIntegrationTree(HoI4::Localisation& hoi4Localisations)
{
	nationalFocus->addIntegratePuppetsBranch(tag, puppets, hoi4Localisations);
}


void HoI4::Country::addFocusTreeBranch(const std::string& branch, OnActions& onActions)
{
	nationalFocus->addBranch(tag, branch, onActions);
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


bool HoI4::Country::hasMonarchIdea() const
{
	return (oldGovernment == "prussian_constitutionalism" || oldGovernment == "hms_government") &&
			 (governmentIdeology != "absolutist") && (leaderIdeology != "absolute_monarchy_neutral");
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
const bool HoI4::Country::isEligibleEnemy(std::string target)
{
	std::set<std::string> allies;
	if (faction)
	{
		allies = faction->getLeader()->getAllies();
		allies.insert(faction->getLeader()->getTag());
	}

	return !allies.contains(target) && !puppets.contains(target) && target != puppetMaster;
}

std::optional<std::string> HoI4::Country::getDominionTag(const std::string& region)
{
	if (generatedDominions.find(region) == generatedDominions.end())
	{
		return std::nullopt;
	}
	return generatedDominions.at(region);
}