#ifndef HOI4_COUNTRY_H_
#define HOI4_COUNTRY_H_



#include "Color.h"
#include "Date.h"
#include "Diplomacy/Faction.h"
#include "Diplomacy/HoI4AIStrategy.h"
#include "Diplomacy/HoI4Relations.h"
#include "Diplomacy/HoI4War.h"
#include "HoI4FocusTree.h"
#include "Ideologies/Ideologies.h"
#include "Leaders/Admiral.h"
#include "Leaders/CountryLeader.h"
#include "Leaders/General.h"
#include "Map/CoastalProvinces.h"
#include "Mappers/Country/CountryMapper.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/Government/GovernmentMapper.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Mappers/Ideology/IdeologyMapper.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Technology/TechMapper.h"
#include "Military/Airplane.h"
#include "Military/HoI4Army.h"
#include "MilitaryMappings/MtgUnitMappings.h"
#include "MilitaryMappings/UnitMappings.h"
#include "Names/Names.h"
#include "Navies/Navies.h"
#include "Navies/NavyNames.h"
#include "Operatives/Operative.h"
#include "ProvinceDefinitions.h"
#include "Regions/Regions.h"
#include "ShipTypes/ShipVariants.h"
#include "States/HoI4State.h"
#include "Technologies.h"
#include "V2World/Countries/Country.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Politics/Party.h"
#include "V2World/World/World.h"
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Country
{
  public:
	explicit Country(std::string tag,
		 const Vic2::Country& sourceCountry,
		 Names& names,
		 Mappers::GraphicsMapper& graphicsMapper,
		 const Mappers::CountryMapper& countryMap,
		 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
		 Localisation& hoi4Localisations);
	explicit Country(const std::string& tag_,
		 const Country& owner,
		 const std::string& region_,
		 const Regions& regions,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names,
		 Localisation& hoi4Localisations);

	void determineCapitalFromVic2(const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates);
	void determineBestCapital(const std::map<int, State>& allStates);
	void setCapitalRegionFlag(const Regions& regions);
	void setGovernmentToExistingIdeology(const std::set<std::string>& majorIdeologies,
		 const Ideologies& ideologies,
		 const Mappers::GovernmentMapper& governmentMap,
		 bool debug);
	void createLeader(Names& names, Mappers::GraphicsMapper& graphicsMapper);
	void convertGovernment(const Vic2::World& sourceWorld,
		 const Mappers::GovernmentMapper& governmentMap,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names,
		 bool debug);
	void convertParties(const std::set<std::string>& majorIdeologies,
		 const Mappers::IdeologyMapper& ideologyMapper,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations);
	void convertIdeologySupport(const std::set<std::string>& majorIdeologies,
		 const Mappers::IdeologyMapper& partyMapper);
	void determineShipVariants(const PossibleShipVariants& possibleVariants);
	void convertNavies(const UnitMappings& unitMap,
		 const MtgUnitMappings& mtgUnitMap,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates,
		 const ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper);
	void convertConvoys(const UnitMappings& unitMap);
	void convertAirForce(const UnitMappings& unitMap);
	void convertArmies(const militaryMappings& theMilitaryMappings,
		 const HoI4::States& theStates,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void convertTechnology(const Mappers::TechMapper& techMapper, const Mappers::ResearchBonusMapper& theTechMapper);
	void addState(const State& state);
	void addCoreState(const int stateId) { coreStates.insert(stateId); }
	void calculateIndustry(const std::map<int, State>& allStates);
	void transferPuppets(const std::set<std::string>& transferingPuppets, std::shared_ptr<HoI4::Country> dominion);
	void addGenericFocusTree(const std::set<std::string>& majorIdeologies);
	void addPuppetsIntegrationTree(HoI4::Localisation& hoi4Localisations);
	void addFocusTreeBranch(const std::string& branch, OnActions& onActions);
	void adjustResearchFocuses() const;

	void setSphereLeader(const std::string& SphereLeader) { sphereLeader = SphereLeader; }
	void setFaction(const std::shared_ptr<const Faction>& newFaction) { faction = newFaction; }
	void giveNationalFocus(std::unique_ptr<HoI4FocusTree>& NF) { nationalFocus = std::move(NF); }
	void setGreatPower() { greatPower = true; }
	void setPuppetMaster(const std::string& _master) { puppetMaster = _master; }
	void addPuppet(const std::string& countryTag) { puppets.insert(countryTag); }

	void makeNavalTreatyAdherent() { navalTreatyAdherent = true; }
	void makeGreatestNavalPower() { greatestNavalPower = true; }
	void setNumberOfAdherents(int num) { numAdherents = num; }

	[[nodiscard]] std::optional<HoI4::Relations> getRelations(const std::string& withWhom) const;
	[[nodiscard]] double getStrengthOverTime(const double& years) const;
	static double getMilitaryStrength();
	[[nodiscard]] float getNavalStrength() const;
	[[nodiscard]] double getEconomicStrength(const double& years) const;
	[[nodiscard]] bool areElectionsAllowed() const;
	[[nodiscard]] std::optional<Faction> getFaction() const;
	[[nodiscard]] std::optional<HoI4FocusTree> getNationalFocus() const;
	[[nodiscard]] bool hasMonarchIdea() const;

	[[nodiscard]] const std::string& getTag() const { return tag; }
	[[nodiscard]] const auto& getOldTag() const { return oldTag; }
	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getAdjective() const { return adjective; }
	[[nodiscard]] const std::string& getFilename() const { return filename; }
	[[nodiscard]] const std::string& getCommonCountryFile() const { return commonCountryFile; }
	[[nodiscard]] bool isHuman() const { return human; }

	[[nodiscard]] const auto& getMonarchIdeaTexture() const { return monarchIdeaTexture; }

	[[nodiscard]] const auto& getPrimaryCulture() const { return primaryCulture; }
	[[nodiscard]] const auto& getPrimaryCultureGroup() const { return primaryCultureGroup; }

	[[nodiscard]] const auto& getColor() const { return color; }
	[[nodiscard]] const std::string& getGraphicalCulture() const { return graphicalCulture; }
	[[nodiscard]] const std::string& getGraphicalCulture2d() const { return graphicalCulture2d; }
	[[nodiscard]] const auto& getArmyPortraits() const { return armyPortraits; }
	[[nodiscard]] const auto& getNavyPortraits() const { return navyPortraits; }
	[[nodiscard]] const auto& getCommunistAdvisorPortrait() const { return communistAdvisorPortrait; }
	[[nodiscard]] const auto& getDemocraticAdvisorPortrait() const { return democraticAdvisorPortrait; }
	[[nodiscard]] const auto& getNeutralityAdvisorPortrait() const { return neutralityAdvisorPortrait; }
	[[nodiscard]] const auto& getAbsolutistAdvisorPortrait() const { return absolutistAdvisorPortrait; }
	[[nodiscard]] const auto& getRadicalAdvisorPortrait() const { return radicalAdvisorPortrait; }
	[[nodiscard]] const auto& getFascistAdvisorPortrait() const { return fascistAdvisorPortrait; }

	[[nodiscard]] bool hasProvinces() const { return !provinces.empty(); }
	[[nodiscard]] const std::set<int>& getProvinces() const { return provinces; }
	[[nodiscard]] const std::set<int>& getStates() const { return states; }
	[[nodiscard]] std::optional<int> getCapitalState() const { return capitalState; }
	[[nodiscard]] std::optional<int> getCapitalProvince() const { return capitalProvince; }
	[[nodiscard]] const auto& getCoreStates() const { return coreStates; }

	[[nodiscard]] const std::string& getOldGovernment() const { return oldGovernment; }
	[[nodiscard]] const std::string& getGovernmentIdeology() const { return governmentIdeology; }
	[[nodiscard]] const std::string& getLeaderIdeology() const { return leaderIdeology; }
	[[nodiscard]] const auto& getRulingParty() const { return rulingParty; }
	[[nodiscard]] const std::set<Vic2::Party>& getParties() const { return parties; }
	[[nodiscard]] const std::map<std::string, int>& getIdeologySupport() const { return ideologySupport; }
	[[nodiscard]] const date& getLastElection() const { return lastElection; }
	[[nodiscard]] int getStability() const { return stability; }
	[[nodiscard]] int getWarSupport() const { return warSupport; }
	[[nodiscard]] const std::string& getMobilizationLaw() const { return mobilizationLaw; }
	[[nodiscard]] const std::string& getEconomicLaw() const { return economicLaw; }
	[[nodiscard]] const std::string& getTradeLaw() const { return tradeLaw; }
	[[nodiscard]] const auto& getLeaders() const { return leaders; }

	[[nodiscard]] auto getTechnologyCount() const
	{
		if (theTechnologies)
		{
			return theTechnologies->getTechnologyCount();
		}
		else
		{
			return 0;
		}
	}
	[[nodiscard]] const std::optional<technologies>& getTechnologies() const { return theTechnologies; }
	[[nodiscard]] const std::set<std::string>& getIdeas() const { return ideas; }
	[[nodiscard]] const auto& getFlags() const { return flags; }

	[[nodiscard]] double getMilitaryFactories() const { return militaryFactories; }
	[[nodiscard]] double getCivilianFactories() const { return civilianFactories; }
	[[nodiscard]] double getDockyards() const { return dockyards; }
	[[nodiscard]] int32_t getEmployedWorkers() const { return employedWorkers; }

	[[nodiscard]] const Army& getArmy() const { return theArmy; }
	[[nodiscard]] const auto& getDivisionLocations() const { return theArmy.getDivisionLocations(); }
	[[nodiscard]] const ShipVariants& getTheShipVariants() const { return *theShipVariants; }
	[[nodiscard]] const Navies& getNavies() const { return *theNavies; }
	[[nodiscard]] const auto& getNavyNames() const { return navyNames; }
	[[nodiscard]] int getConvoys() const { return convoys; }
	[[nodiscard]] const std::vector<Airplane>& getPlanes() const { return planes; }
	[[nodiscard]] const std::map<std::string, unsigned int>& getEquipmentStockpile() const { return equipmentStockpile; }
	[[nodiscard]] const std::vector<General>& getGenerals() const { return generals; }
	[[nodiscard]] const std::vector<Admiral>& getAdmirals() const { return admirals; }

	[[nodiscard]] const auto& getOperatives() const { return operatives_; }

	[[nodiscard]] const std::map<std::string, HoI4::Relations>& getRelations() const { return relations; }
	[[nodiscard]] const auto& getAIStrategies() const { return aiStrategies; }
	[[nodiscard]] const auto& getConquerStrategies() const { return conquerStrategies; }
	[[nodiscard]] const std::vector<War>& getWars() const { return wars; }
	[[nodiscard]] double getThreat() const { return threat; }
	[[nodiscard]] bool isInFaction() const { return faction.operator bool(); }
	[[nodiscard]] const std::string& getSphereLeader() const { return sphereLeader; }
	[[nodiscard]] const std::set<std::string>& getAllies() const { return allies; }
	[[nodiscard]] const std::set<std::string>& getPuppets() const { return puppets; }
	[[nodiscard]] const std::string& getPuppetMaster() const { return puppetMaster; }
	[[nodiscard]] const std::string& getPuppetMasterOldTag() const { return puppetMasterOldTag; }
	[[nodiscard]] bool isGreatPower() const { return greatPower; }
	[[nodiscard]] bool isCivilized() const { return civilized; }
	[[nodiscard]] bool isGeneratedDominion() const { return generatedDominion; }
	[[nodiscard]] const auto& getRegion() const { return region; }

	[[nodiscard]] bool isNavalTreatyAdherent() const { return navalTreatyAdherent; }
	[[nodiscard]] bool isGreatestNavalPower() const { return greatestNavalPower; }
	[[nodiscard]] const auto& getNumAdherents() const { return numAdherents; }

	std::set<std::string>& editAllies() { return allies; }

	void addLeader(CountryLeader leader) { leaders.push_back(std::move(leader)); }
	void addGPInfluence(std::string GPTag, int influenceValue) { GPInfluences.insert({GPTag, influenceValue}); }
	[[nodiscard]] const std::map<std::string, double>& getSpherelings() const { return spherelings; }
	void addSphereling(std::string sphereling) { spherelings.insert(make_pair(sphereling, 0.5)); }
	void setSpherelingAutonomy(std::string sphereling, double autonomy)
	{
		spherelings.find(sphereling)->second = autonomy;
	}
	double calculateInfluenceFactor();
	const auto& getGuaranteed() const { return guaranteed; }
	void addGuaranteed(std::string guaranteedTag) { guaranteed.push_back(guaranteedTag); }

	[[nodiscard]] const bool isEligibleEnemy(std::string target);

	void addGeneratedDominion(const std::string& region, const std::string& tag) { generatedDominions[region] = tag; }
	std::optional<std::string> getDominionTag(const std::string& region);
	void addGlobalEventTarget(const std::string& name) { globalEventTargets.insert(name); }

	[[nodiscard]] const auto& getGlobalEventTargets() const { return globalEventTargets; }

  private:
	void determineFilename();
	void initIdeas(Names& names, Localisation& hoi4Localisations) const;
	void createOperatives(const Mappers::GraphicsMapper& graphicsMapper, Names& names);
	void convertLaws();
	void convertLeaders(const Vic2::Country& sourceCountry);
	void convertMonarchIdea(const Mappers::GraphicsMapper& graphicsMapper,
		 Names& names,
		 Localisation& hoi4Localisations);
	void convertRelations(const Mappers::CountryMapper& countryMap, const Vic2::Country& sourceCountry);
	void convertStrategies(const Mappers::CountryMapper& countryMap, const Vic2::Country& sourceCountry);
	void convertWars(const Vic2::Country& sourceCountry, const Mappers::CountryMapper& countryMap);

	bool attemptToPutCapitalInPreferredNonWastelandOwned(const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates);
	bool attemptToPutCapitalInNonWastelandOwned(const std::map<int, State>& allStates);
	bool attemptToPutCapitalInPreferredWastelandOwned(const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates);
	bool attemptToPutCapitalInAnyOwned(const std::map<int, State>& allStates);
	bool attemptToPutCapitalInPreferredNonWastelandCored(const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates);
	bool attemptToPutCapitalInAnyNonWastelandCored(const std::map<int, State>& allStates);
	bool attemptToPutCapitalInPreferredWastelandCored(const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates);
	bool attemptToPutCapitalInAnyCored(const std::map<int, State>& allStates);
	[[nodiscard]] std::vector<std::string> getShipNames(const std::string& category) const;

	void convertStockpile();
	float getSourceCountryGoodAmount(const std::string& goodType);

	std::string tag;
	std::string oldTag;
	std::optional<std::string> name;
	std::optional<std::string> adjective;
	std::string filename;
	std::string commonCountryFile;
	bool human = false;
	std::optional<std::string> lastDynasty;

	std::string primaryCulture;
	std::string primaryCultureGroup;

	commonItems::Color color;
	std::string graphicalCulture = "western_european_gfx";
	std::string graphicalCulture2d = "western_european_2d";
	std::vector<std::string> armyPortraits;
	std::vector<std::string> navyPortraits;
	std::string communistAdvisorPortrait;
	std::string democraticAdvisorPortrait;
	std::string neutralityAdvisorPortrait;
	std::string absolutistAdvisorPortrait;
	std::string radicalAdvisorPortrait;
	std::string fascistAdvisorPortrait;

	std::set<int> provinces;
	std::set<int> states;
	std::optional<int> capitalState;
	std::optional<int> capitalProvince;
	int oldCapital;
	std::set<int> coreStates;

	std::string oldGovernment;
	std::string governmentIdeology = "neutrality";
	std::string leaderIdeology = "anarchism";
	std::optional<Vic2::Party> rulingParty;
	std::set<Vic2::Party> parties;
	std::map<std::string, double> upperHouseComposition;
	std::map<std::string, int> ideologySupport{std::make_pair("neutrality", 100)};
	date lastElection;
	int stability = 60;
	int warSupport = 60;
	std::string mobilizationLaw = "volunteer_only";
	std::string economicLaw = "civilian_economy";
	std::string tradeLaw = "export_focus";

	std::vector<CountryLeader> leaders;

	std::set<std::string> oldTechnologiesAndInventions;
	std::optional<technologies> theTechnologies;
	std::set<std::string> ideas;
	std::unique_ptr<HoI4FocusTree> nationalFocus;
	std::set<std::string> flags;

	std::string monarchIdeaTexture = "gfx/interface/ideas/idea_george_v.dds";

	double militaryFactories = 0.0;
	double civilianFactories = 0.0;
	double dockyards = 0.0;
	int32_t employedWorkers = 0;

	std::vector<Vic2::Army> oldArmies;
	Army theArmy;
	std::unique_ptr<ShipVariants> theShipVariants;
	std::unique_ptr<Navies> theNavies;
	NavyNames navyNames;
	int convoys = 0;
	std::vector<Airplane> planes;
	std::map<std::string, unsigned int> equipmentStockpile;
	std::vector<General> generals;
	std::vector<Admiral> admirals;
	std::map<std::string, std::vector<std::string>> shipNames;

	std::vector<Operative> operatives_;

	std::map<std::string, HoI4::Relations> relations;
	std::vector<HoI4::AIStrategy> aiStrategies;
	std::vector<HoI4::AIStrategy> conquerStrategies;
	bool atWar = false;
	std::vector<War> wars;
	double threat = 0.0;
	std::shared_ptr<const Faction> faction;
	std::string sphereLeader;
	std::set<std::string> allies;
	std::set<std::string> puppets;
	std::map<std::string, std::string> generatedDominions;
	std::string puppetMaster;
	std::string puppetMasterOldTag;
	bool greatPower = false;
	bool civilized = false;
	bool generatedDominion = false;
	std::string region;

	std::map<std::string, int> GPInfluences;
	std::map<std::string, double> spherelings;
	std::vector<std::string> guaranteed;

	bool navalTreatyAdherent = false;
	bool greatestNavalPower = false;
	std::optional<int> numAdherents;

	std::mt19937 generator;

	std::map<std::string, float> sourceCountryGoods;
	std::set<std::string> globalEventTargets;
};

} // namespace HoI4



#endif // HOI4_COUNTRY_H_