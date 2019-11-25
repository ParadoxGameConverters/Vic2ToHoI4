#ifndef HoI4COUNTRY_H_
#define HoI4COUNTRY_H_



#include "HoI4Airforce.h"
#include "HoI4Army.h"
#include "Division.h"
#include "DivisionTemplate.h"
#include "HoI4FocusTree.h"
#include "HOI4Ideology.h"
#include "HoI4Leader.h"
#include "HoI4Province.h"
#include "HoI4Relations.h"
#include "HoI4War.h"
#include "MilitaryMappings/MtgUnitMappings.h"
#include "MilitaryMappings/UnitMappings.h"
#include "Navies/Navies.h"
#include "ShipTypes/PossibleShipVariants.h"
#include "ShipTypes/ShipVariant.h"
#include "ShipTypes/ShipVariants.h"
#include "States/HoI4State.h"
#include "Technologies.h"
#include "../Color.h"
#include "Date.h"
#include "../Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include "../V2World/Army.h"
#include "../V2World/Party.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{
class Country;
class World;
}


class HoI4Faction;
class HoI4Ideology;


namespace HoI4
{
class Advisor;
class coastalProvinces;
class namesMapper;
class State;
class HoI4UnitType;
class World;
struct advisorCompare;
}


namespace mappers
{
class techMapper;
}


class CountryMapper;
class governmentMapper;
class graphicsMapper;



class HoI4Country
{
	public:
		HoI4Country(const std::string& _tag, const HoI4::World* _theWorld): theWorld(_theWorld), tag(_tag) {};

		void initFromV2Country(
			const Vic2::World& _srcWorld,
			const Vic2::Country* _srcCountry,
			const std::map<int, int>& stateMap,
			const std::map<int, HoI4::State*>& states,
			HoI4::namesMapper& theNames,
			const graphicsMapper& theGraphics,
			const CountryMapper& countryMap,
			const mappers::FlagsToIdeasMapper& flagsToIdeasMapper
		);
		void setGovernmentToExistingIdeology(const std::set<std::string>& majorIdeologies, const std::map<std::string, HoI4Ideology*>& ideologies, const governmentMapper& governmentMap);
		void convertGovernment(const Vic2::World& _srcWorld, const governmentMapper& governmentMap);
		void convertParties(const std::set<std::string>& majorIdeologies, const governmentMapper& governmentMap);
		void convertIdeologySupport(const std::set<std::string>& majorIdeologies, const governmentMapper& governmentMap);
		void determineShipVariants(const std::vector<HoI4::shipVariant>& possibleVariants);
		void convertNavies(
			const HoI4::UnitMappings& unitMap,
			const HoI4::MtgUnitMappings& mtgUnitMap,
			const HoI4::coastalProvinces& theCoastalProvinces,
			const std::map<int, int>& provinceToStateIDMap
		);
		void convertConvoys(const HoI4::UnitMappings& unitMap);
		void convertAirforce(const HoI4::UnitMappings& unitMap);
		void convertArmies(const HoI4::militaryMappings& theMilitaryMappings);
		void convertTechnology(std::unique_ptr<mappers::techMapper>& theTechMapper);
		void addState(HoI4::State* _state);
		void calculateIndustry();
		void reportIndustry(std::ofstream& out);
		void addVPsToCapital(int VPs);
		void addGenericFocusTree(const std::set<std::string>& majorIdeologies);
		void adjustResearchFocuses();
		void outputToCommonCountriesFile(std::ofstream& countriesFile) const;
		void outputColors(std::ofstream& out) const;
		void outputToNamesFiles(std::ofstream& namesFile, const HoI4::namesMapper& theNames) const;
		void outputToUnitNamesFiles(std::ofstream& unitNamesFile) const;
		void output(const std::set<const HoI4::Advisor*, HoI4::advisorCompare>& ideologicalMinisters, const std::vector<HoI4::DivisionTemplateType>& divisionTemplates, HoI4::namesMapper& theNames, graphicsMapper& theGraphics) const;
		void outputIdeaGraphics(std::ofstream& ideasFile, graphicsMapper& graphics) const;

		void setSphereLeader(const std::string& SphereLeader) { sphereLeader = SphereLeader; }
		void		setFaction(std::shared_ptr<const HoI4Faction> newFaction) { faction = newFaction; }
		void		setFactionLeader() { factionLeader = true; }
		void addNationalFocus(std::shared_ptr<HoI4FocusTree> NF) { nationalFocus = NF; }
		void setGreatPower() { greatPower = true; }

		std::optional<const HoI4Relations*> getRelations(std::string withWhom) const;
		double getStrengthOverTime(double years) const;
		double getMilitaryStrength() const;
		double getEconomicStrength(double years) const;

		bool isHuman() const { return human; }
		const std::map<std::string, HoI4Relations*>&	getRelations() const { return relations; }
		std::set<int>									getProvinces() const { return provinces; }
		std::string										getTag() const { return tag; }
		const Vic2::Country*							getSourceCountry() const { return srcCountry; }
		std::shared_ptr<const HoI4Faction> getFaction() const { return faction; }
		std::string getGovernmentIdeology() const { return governmentIdeology; }
		std::map<std::string, int> getIdeologySupport() const { return ideologySupport; }
		const std::set<std::string>&						getAllies() const { return allies; }
		const std::set<std::string>&							getPuppets() const { return puppets; }
		const std::string&								getPuppetmaster() const { return puppetMaster; }
		const std::map<std::string, double>&						getPracticals() const { return practicals; }
		std::vector<int>									getBrigs() const { return brigs; }
		HoI4::State* getCapitalState() const { return capitalState; }
		int											getCapitalStateNum() const { return capitalStateNum; }
		const std::string									getSphereLeader() const { return sphereLeader; }
		const Vic2::Party getRulingParty() const { return rulingParty; }
		std::set<Vic2::Party, std::function<bool (const Vic2::Party&, const Vic2::Party&)>> getParties() const { return parties; }
		std::map<int, HoI4::State*> getStates() const { return states; }
		bool isInFaction() const { return faction != nullptr; }
		bool isCivilized() const { return civilized; }

		int getTechnologyCount() const { return technologies->getTechnologyCount(); }
		int getProvinceCount() const { return provinceCount; }
		bool isGreatPower() const { return greatPower; }

		void setProvinceCount(int count) { provinceCount = count; }
		void setPuppetmaster(const std::string& _master) { puppetMaster = _master; }
		void addPuppet(const std::string& countryTag) { puppets.insert(countryTag); }

		std::set<std::string>&								editAllies() { return allies; }

	private:
		HoI4Country(const HoI4Country&) = delete;
		HoI4Country& operator=(const HoI4Country&) = delete;

		void determineFilename();
		void initIdeas(HoI4::namesMapper& theNames);
		void convertLaws();
		void convertLeaders(const graphicsMapper& theGraphics);
		void convertRelations(const CountryMapper& countryMap);
		void convertWars(const Vic2::Country& sourceCountry, const CountryMapper& countryMap);
		void determineCapitalFromVic2(const std::map<int, int>& provinceToStateIDMap, const std::map<int, HoI4::State*>& states);
		bool isStateValidForCapital(int capitalState, const std::map<int, HoI4::State*>& states);
		bool isThisStateOwnedByUs(const HoI4::State* state) const;
		bool isThisStateACoreWhileWeOwnNoStates(const HoI4::State* state) const;
		void setCapitalInCapitalState(int capitalProvince);
		void findBestCapital();

		void addProvince(int _province);

		void outputNamesSet(std::ofstream& namesFile, const std::optional<std::vector<std::string>>& names, const std::string& tabs) const;
		void outputHistory(HoI4::namesMapper& theNames, graphicsMapper& theGraphics) const;
		void outputCapital(std::ofstream& output) const;
		void outputResearchSlots(std::ofstream& output) const;
		void outputThreat(std::ofstream& output) const;
		void outputWars(std::ostream& output) const;
		void outputOOB(const std::vector<HoI4::DivisionTemplateType>& divisionTemplates) const;
		void outputConvoys(std::ofstream& output) const;
		void outputEquipmentStockpile(std::ofstream& output) const;
		void outputPuppets(std::ofstream& output) const;
		void outputPolitics(std::ofstream& output) const;
		void outputRelations(std::ofstream& output) const;
		bool areElectionsAllowed(void) const;
		void outputFactions(std::ofstream& output) const;
		void outputIdeas(std::ofstream& output) const;
		void outputStability(std::ofstream& output) const;
		void outputWarSupport(std::ofstream& output) const;
		void outputCountryLeader(std::ofstream& output, HoI4::namesMapper& theNames, graphicsMapper& theGraphics) const;
		void outputCommanders(std::ofstream& output) const;
		void outputOOBLines(std::ostream& output) const;
		void outputCommonCountryFile() const;
		void outputAdvisorIdeas(const std::set<const HoI4::Advisor*, HoI4::advisorCompare>& ideologicalAdvisors) const;
		void outputUnitType(std::ofstream& unitNamesFile, const std::string& sourceUnitType, const std::string& destUnitType, const std::string& defaultName) const;


		const HoI4::World* theWorld = nullptr;
		const Vic2::Country* srcCountry = nullptr;
		std::string filename;

		bool human = false;

		std::string governmentIdeology = "neutrality";
		std::string leaderIdeology = "conservatism_neutral";
		Vic2::Party rulingParty;
		std::set<Vic2::Party, std::function<bool (const Vic2::Party&, const Vic2::Party&)>> parties;
		std::map<std::string, int> ideologySupport;
		date lastElection;

		std::string sphereLeader;
		std::string								tag;
		std::set<int>							provinces;
		std::map<int, HoI4::State*> states;
		int									capitalStateNum = 0;
		HoI4::State*							capitalState = nullptr;
		std::string								commonCountryFile;

		std::unique_ptr<HoI4::technologies> technologies;

		std::map<std::string, HoI4Relations*>	relations;
		ConverterColor::Color color;
		double stability = 0.50;
		double warSupport = 0.50;
		std::shared_ptr<const HoI4Faction>	faction;
		bool									factionLeader = false;
		std::set<std::string>							allies;
		std::set<std::string> puppets;
		std::string puppetMaster;
		std::map<std::string, double>				practicals;
		std::string graphicalCulture = "western_european_gfx";
		std::string graphicalCulture2d = "western_european_2d";
		bool									majorNation = false;
		bool									civilized = false;
		std::vector<int>							brigs;
		int									convoys = 0;
		
		int provinceCount = 0;
		long armyStrength = 0;
		double militaryFactories = 0.0;
		double civilianFactories = 0.0;
		double dockyards = 0.0;
		double threat = 0.0;

		// laws
		std::string mobilizationLaw = "volunteer_only";
		std::string economicLaw = "civilian_economy";
		std::string tradeLaw = "export_focus";

		bool greatPower = false;

		std::set<std::string> ideas;

		bool atWar = false;
		std::vector<HoI4::War> wars;

		// military stuff
		HoI4::Army theArmy;
		std::unique_ptr<HoI4::shipVariants> theShipVariants;
		std::unique_ptr<HoI4::Navies> theNavies;
		std::vector<HoI4Airplane> planes;
		std::map<std::string, int> equipmentStockpile;
		std::vector<HoI4::General> generals;
		std::vector<HoI4::Admiral> admirals;

		std::shared_ptr<HoI4FocusTree> nationalFocus;
};



#endif	// HoI4COUNTRY_H_