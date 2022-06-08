#ifndef HOI4_COUNTRY_H_
#define HOI4_COUNTRY_H_



#include "Color.h"
#include "Date.h"
#include "Diplomacy/Faction.h"
#include "Diplomacy/HoI4AIStrategy.h"
#include "Diplomacy/HoI4Relations.h"
#include "Diplomacy/HoI4War.h"
#include "HOI4World/Characters/Character.h"
#include "HoI4FocusTree.h"
#include "Ideologies/Ideologies.h"
#include "Map/CoastalProvinces.h"
#include "Mappers/Country/CountryMapper.h"
#include "Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "Mappers/Government/GovernmentMapper.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Mappers/Ideology/IdeologyMapper.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Technology/TechMapper.h"
#include "Maps/ProvinceDefinitions.h"
#include "Military/Airplane.h"
#include "Military/HoI4Army.h"
#include "MilitaryMappings/MtgUnitMappings.h"
#include "MilitaryMappings/UnitMappings.h"
#include "Names/Names.h"
#include "Navies/Navies.h"
#include "Navies/NavyNames.h"
#include "Operatives/Operative.h"
#include "Regions/Regions.h"
#include "ShipTypes/ShipVariants.h"
#include "States/HoI4State.h"
#include "TankDesigns/TankDesigns.h"
#include "Technologies.h"
#include "V2World/Countries/Country.h"
#include "V2World/Localisations/Vic2Localisations.h"
#include "V2World/Politics/Party.h"
#include "V2World/World/World.h"
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Country
{
  public:
	// For creating countries from Vic2 countries
	explicit Country(std::string tag,
		 const Vic2::Country& sourceCountry,
		 Names& names,
		 Mappers::GraphicsMapper& graphicsMapper,
		 const Mappers::CountryMapper& countryMap,
		 const Mappers::FlagsToIdeasMapper& flagsToIdeasMapper,
		 Localisation& hoi4Localisations,
		 const date& startDate,
		 const Mappers::ProvinceMapper& theProvinceMapper,
		 const States& worldStates,
		 Character::Factory& characterFactory);

	/// For creating generated dominions
	explicit Country(const std::shared_ptr<Country> owner,
		 const std::string& region_,
		 const Regions& regions,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names);

	// For creating unrecognized nations
	explicit Country(const std::string& region_,
		 const Regions& regions,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names);

	void addTag(const std::string& tag_, Names& names, Localisation& hoi4Localisations);
	void addMonarchIdea(const Country& owner);
	void determineCapitalFromVic2(const Mappers::ProvinceMapper& theProvinceMapper,
		 const std::map<int, int>& provinceToStateIDMap,
		 const std::map<int, State>& allStates);
	void determineBestCapital(const std::map<int, State>& allStates);
	void setCapitalRegionFlag(const Regions& regions);
	void setGovernmentToExistingIdeology(const std::set<std::string>& majorIdeologies,
		 const Ideologies& ideologies,
		 const Mappers::GovernmentMapper& governmentMap,
		 Localisation& hoi4Localisations,
		 bool debug);
	void createLeader(Names& names,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Character::Factory& characterFactory,
		 Localisation& localisation);
	void convertGovernment(const Vic2::World& sourceWorld,
		 const Mappers::GovernmentMapper& governmentMap,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations,
		 Mappers::GraphicsMapper& graphicsMapper,
		 Names& names,
		 std::mt19937& femaleChanceGenerator,
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
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper);
	void convertConvoys(const UnitMappings& unitMap);
	void convertAirForce(const UnitMappings& unitMap);
	void convertArmies(const militaryMappings& theMilitaryMappings,
		 const HoI4::States& theStates,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);
	void addTankDesigns(const PossibleTankDesigns& possibleDesigns);
	void convertTechnology(const Mappers::TechMapper& techMapper, const Mappers::ResearchBonusMapper& theTechMapper);
	void addState(const State& state);
	void addCoreState(const int stateId) { coreStates.insert(stateId); }
	void addClaimedState(const int stateId) { claimedStates.insert(stateId); }
	void calculateIndustry(const std::map<int, State>& allStates);
	void transferPuppets(const std::set<std::shared_ptr<HoI4::Country>>& transferringPuppets,
		 std::shared_ptr<HoI4::Country> dominion,
		 const Regions& theRegions);
	void addEmptyFocusTree();
	void addGenericFocusTree(const std::set<std::string>& majorIdeologies);
	void addPuppetsIntegrationTree(HoI4::Localisation& hoi4Localisations);
	void addFocusTreeBranch(const std::string& branch, OnActions& onActions);
	void adjustResearchFocuses() const;

	void setSphereLeader(const std::string& SphereLeader) { sphereLeader = SphereLeader; }
	void setFaction(const std::shared_ptr<const Faction>& newFaction) { faction = newFaction; }
	void giveNationalFocus(std::unique_ptr<HoI4FocusTree>& NF) { nationalFocus = std::move(NF); }
	void setGreatPower() { greatPower = true; }
	void setPuppetMaster(const std::shared_ptr<Country> master) { puppetMaster = master; }
	void addPuppet(const std::shared_ptr<Country> puppet, const Regions& theRegions);

	void makeNavalTreatyAdherent() { navalTreatyAdherent = true; }
	void makeGreatestNavalPower() { greatestNavalPower = true; }
	void setNumberOfAdherents(int num) { numAdherents = num; }

	void setPrimaryCulture(std::string_view culture) { primaryCulture = culture; }

	void addUnbuiltCanal(const std::string& unbuiltCanal) { unbuiltCanals.push_back(unbuiltCanal); }

	void determineDominionAreas(const std::unique_ptr<Maps::MapData>& theMapData,
		 const std::map<int, HoI4::State>& allStates,
		 const std::map<int, int>& provinceToStateIdMap);
	void addProvincesToArea(int startingProvince,
		 std::set<int>& area,
		 const std::unique_ptr<Maps::MapData>& theMapData,
		 const std::map<int, HoI4::State>& allStates,
		 const std::map<int, int>& provinceToStateIdMap);
	bool isProvinceInDominionArea(int province);

	[[nodiscard]] std::optional<HoI4::Relations> getRelations(const std::string& withWhom) const;
	[[nodiscard]] std::optional<date> getTruceUntil(const std::string& withWhom) const;
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
	[[nodiscard]] const auto& getName() const { return name_; }
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
	[[nodiscard]] const auto& getFemaleMilitaryPortraits() const { return femaleMilitaryPortraits; }
	[[nodiscard]] const auto& getFemaleMonarchPortraits() const { return femaleMonarchPortraits; }
	[[nodiscard]] const auto& getFemaleIeologicalPortraits() const { return femaleIdeologicalPortraits; }
	[[nodiscard]] const auto& getMaleCommunistPortraits() const { return maleCommunistPortraits; }
	[[nodiscard]] const auto& getMaleDemocraticPortraits() const { return maleDemocraticPortraits; }
	[[nodiscard]] const auto& getMaleFascistPortraits() const { return maleFascistPortraits; }
	[[nodiscard]] const auto& getMaleAbsolutistPortraits() const { return maleAbsolutistPortraits; }
	[[nodiscard]] const auto& getMaleNeutralPortraits() const { return maleNeutralPortraits; }
	[[nodiscard]] const auto& getMaleRadicalPortraits() const { return maleRadicalPortraits; }
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
	[[nodiscard]] const auto& getClaimedStates() const { return claimedStates; }

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
	[[nodiscard]] const auto& getCharacters() const { return characters_; }

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
	[[nodiscard]] const TankDesigns& getTankDesigns() const { return *tankDesigns; }
	[[nodiscard]] const ShipVariants& getTheShipVariants() const { return *theShipVariants; }
	[[nodiscard]] std::optional<Navies> getNavies() const;
	[[nodiscard]] const auto& getNavyNames() const { return navyNames; }
	[[nodiscard]] int getConvoys() const { return convoys; }
	[[nodiscard]] auto getTrainsMultiplier() const { return trainsMultiplier; }
	[[nodiscard]] const std::vector<Airplane>& getPlanes() const { return planes; }
	[[nodiscard]] const std::map<std::string, unsigned int>& getEquipmentStockpile() const { return equipmentStockpile; }

	[[nodiscard]] const auto& getOperatives() const { return operatives_; }

	[[nodiscard]] const std::map<std::string, HoI4::Relations>& getRelations() const { return relations; }
	[[nodiscard]] const auto& getAIStrategies() const { return aiStrategies; }
	[[nodiscard]] const auto& getConquerStrategies() const { return conquerStrategies; }
	[[nodiscard]] const std::vector<War>& getWars() const { return wars; }
	[[nodiscard]] double getThreat() const { return threat; }
	[[nodiscard]] bool isInFaction() const { return faction.operator bool(); }
	[[nodiscard]] const std::string& getSphereLeader() const { return sphereLeader; }
	[[nodiscard]] const std::set<std::string>& getAllies() const { return allies; }
	[[nodiscard]] const std::map<std::string, std::string>& getPuppets() const { return puppets; }
	[[nodiscard]] const auto getPuppetMaster() const { return puppetMaster; }
	[[nodiscard]] const std::string& getPuppetMasterOldTag() const { return puppetMasterOldTag; }
	[[nodiscard]] bool isGreatPower() const { return greatPower; }
	[[nodiscard]] bool isCivilized() const { return civilized; }
	[[nodiscard]] bool isGeneratedDominion() const { return generatedDominion; }
	[[nodiscard]] bool isUnrecognizedNation() const { return unrecognizedNation; }
	[[nodiscard]] const auto& getRegion() const { return region; }

	[[nodiscard]] bool isNavalTreatyAdherent() const { return navalTreatyAdherent; }
	[[nodiscard]] bool isGreatestNavalPower() const { return greatestNavalPower; }
	[[nodiscard]] const auto& getNumAdherents() const { return numAdherents; }

	[[nodiscard]] const auto& getUnbuiltCanals() const { return unbuiltCanals; }

	[[nodiscard]] bool hasTankManufacturer() const { return has_tank_manufacturer_; }
	[[nodiscard]] bool hasMotorizedEquipmentManufacturer() const { return has_motorized_equipment_manufacturer_; }
	[[nodiscard]] bool hasInfantryEquipmentManufacturer() const { return has_infantry_equipment_manufacturer_; }
	[[nodiscard]] bool hasArtilleryManufacturer() const { return has_artillery_manufacturer_; }
	[[nodiscard]] bool hasLightAircraftManufacturer() const { return has_light_aircraft_manufacturer_; }
	[[nodiscard]] bool hasMediumAircraftManufacturer() const { return has_medium_aircraft_manufacturer_; }
	[[nodiscard]] bool hasHeavyAircraftManufacturer() const { return has_heavy_aircraft_manufacturer_; }
	[[nodiscard]] bool hasNavalAircraftManufacturer() const { return has_naval_aircraft_manufacturer_; }
	[[nodiscard]] bool hasNavalManufacturer() const { return has_naval_manufacturer_; }
	[[nodiscard]] bool hasIndustrialConcern() const { return has_industrial_concern_; }
	[[nodiscard]] bool hasElectronicsConcern() const { return has_electronics_concern_; }

	std::set<std::string>& editAllies() { return allies; }

	void addCharacter(const Character& character) { characters_.push_back(character); }

	[[nodiscard]] const bool isEligibleEnemy(std::string target) const;

	void convertWars(const Vic2::Country& sourceCountry,
		 const std::set<std::string>& independentCountries,
		 const Mappers::CountryMapper& countryMap,
		 const Mappers::CasusBellis& casusBellis,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const std::map<int, int>& provinceToStateIDMap);

	void addGeneratedDominion(const std::string& region, const std::string& tag) { generatedDominions[region] = tag; }
	std::optional<std::string> getDominionTag(const std::string& region);
	void addGlobalEventTarget(const std::string& name) { globalEventTargets.insert(name); }

	void setTrainsMultiplier(float multiplier) { trainsMultiplier = multiplier; }

	[[nodiscard]] const auto& getGlobalEventTargets() const { return globalEventTargets; }
	[[nodiscard]] const auto& getDominionAreas() const { return dominionAreas; }
	[[nodiscard]] bool isProvinceInCapitalArea(int province) const { return dominionAreas[0].contains(province); }

	void convertStrategies(const Mappers::CountryMapper& countryMap,
		 const Vic2::Country& sourceCountry,
		 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
		 const States& states,
		 const Mappers::ProvinceMapper& provinceMapper);

	[[nodiscard]] std::mt19937& getGenerator() { return generator; }

  private:
	void determineFilename();
	void initIdeas(Names& names, Localisation& hoi4Localisations);
	void createOperatives(const Mappers::GraphicsMapper& graphicsMapper, Names& names);
	void convertLaws();
	void convertLeaders(const Vic2::Country& sourceCountry,
		 Character::Factory& characterFactory,
		 Localisation& localisation);
	void convertMonarch(const std::string& lastMonarch);
	void convertMonarchIdea(const Mappers::GraphicsMapper& graphicsMapper,
		 Names& names,
		 Localisation& hoi4Localisations,
		 std::mt19937& femaleChanceGenerator);
	void convertRelations(const Mappers::CountryMapper& countryMap,
		 const Vic2::Country& sourceCountry,
		 const date& startDate);

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
	bool hasRulingDynasty();

	std::string tag;
	std::string oldTag;
	std::optional<std::string> name_;
	std::optional<std::string> adjective_;
	std::string filename;
	std::string commonCountryFile;
	bool human = false;
	std::optional<std::string> lastDynasty;
	std::pair<std::string, std::string> nextMonarch; // name, regnal number

	std::string primaryCulture;
	std::string primaryCultureGroup;

	commonItems::Color color;
	std::string graphicalCulture = "western_european_gfx";
	std::string graphicalCulture2d = "western_european_2d";
	std::vector<std::string> armyPortraits;
	std::vector<std::string> navyPortraits;
	std::vector<std::string> femaleMilitaryPortraits;
	std::vector<std::string> femaleMonarchPortraits;
	std::vector<std::string> femaleIdeologicalPortraits;
	std::vector<std::string> maleCommunistPortraits;
	std::vector<std::string> maleDemocraticPortraits;
	std::vector<std::string> maleFascistPortraits;
	std::vector<std::string> maleAbsolutistPortraits;
	std::vector<std::string> maleNeutralPortraits;
	std::vector<std::string> maleRadicalPortraits;
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
	std::set<int> claimedStates;

	std::string oldGovernment;
	std::string governmentIdeology = "neutrality";
	std::string leaderIdeology = "dictatorship_neutral";
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

	std::vector<Character> characters_;

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
	std::shared_ptr<Country> puppetMaster;
	std::unique_ptr<TankDesigns> tankDesigns;
	std::unique_ptr<ShipVariants> theShipVariants;
	std::unique_ptr<Navies> theNavies;
	NavyNames navyNames;
	int convoys = 0;
	std::optional<float> trainsMultiplier;
	std::vector<Airplane> planes;
	std::map<std::string, unsigned int> equipmentStockpile;
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
	std::map<std::string, std::string> puppets; // tag, level
	std::map<std::string, std::string> generatedDominions;
	std::string puppetMasterOldTag;
	bool greatPower = false;
	bool civilized = false;
	bool generatedDominion = false;
	bool unrecognizedNation = false;
	std::string region;

	bool navalTreatyAdherent = false;
	bool greatestNavalPower = false;
	std::optional<int> numAdherents;

	std::mt19937 generator;

	std::map<std::string, float> sourceCountryGoods;
	std::set<std::string> globalEventTargets;
	std::vector<std::set<int>> dominionAreas;

	std::vector<std::string> unbuiltCanals;

	bool has_tank_manufacturer_ = false;
	bool has_motorized_equipment_manufacturer_ = false;
	bool has_infantry_equipment_manufacturer_ = false;
	bool has_artillery_manufacturer_ = false;
	bool has_light_aircraft_manufacturer_ = false;
	bool has_medium_aircraft_manufacturer_ = false;
	bool has_heavy_aircraft_manufacturer_ = false;
	bool has_naval_aircraft_manufacturer_ = false;
	bool has_naval_manufacturer_ = false;
	bool has_industrial_concern_ = false;
	bool has_electronics_concern_ = false;
};

} // namespace HoI4



#endif // HOI4_COUNTRY_H_