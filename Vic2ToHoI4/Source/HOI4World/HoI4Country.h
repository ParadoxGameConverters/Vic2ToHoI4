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



namespace HoI4
{

class Country
{
	public:
		Country(const std::string& _tag): tag(_tag) {};

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
		void setGovernmentToExistingIdeology(
			const std::set<std::string>& majorIdeologies,
			const std::map<std::string, HoI4Ideology*>& ideologies,
			const governmentMapper& governmentMap
		);
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
		void addVPsToCapital(int VPs);
		void addGenericFocusTree(const std::set<std::string>& majorIdeologies);
		void adjustResearchFocuses();

		void setSphereLeader(const std::string& SphereLeader) { sphereLeader = SphereLeader; }
		void setFaction(std::shared_ptr<const HoI4Faction> newFaction) { faction = newFaction; }
		void addNationalFocus(std::shared_ptr<HoI4FocusTree> NF) { nationalFocus = NF; }
		void setGreatPower() { greatPower = true; }
		void setPuppetmaster(const std::string& _master) { puppetMaster = _master; }
		void addPuppet(const std::string& countryTag) { puppets.insert(countryTag); }

		std::optional<const HoI4Relations*> getRelations(std::string withWhom) const;
		double getStrengthOverTime(double years) const;
		double getMilitaryStrength() const;
		double getEconomicStrength(double years) const;
		bool areElectionsAllowed() const;

		bool isHuman() const { return human; }
		const std::map<std::string, HoI4Relations*>& getRelations() const { return relations; }
		std::set<int> getProvinces() const { return provinces; }
		std::string getTag() const { return tag; }
		const Vic2::Country* getSourceCountry() const { return srcCountry; }
		std::shared_ptr<const HoI4Faction> getFaction() const { return faction; }
		std::string getGovernmentIdeology() const { return governmentIdeology; }
		std::map<std::string, int> getIdeologySupport() const { return ideologySupport; }
		const std::set<std::string>& getAllies() const { return allies; }
		const std::set<std::string>& getPuppets() const { return puppets; }
		const std::string& getPuppetmaster() const { return puppetMaster; }
		HoI4::State* getCapitalState() const { return capitalState; }
		int getCapitalStateNum() const { return capitalStateNum; }
		const std::string getSphereLeader() const { return sphereLeader; }
		const Vic2::Party getRulingParty() const { return rulingParty; }
		std::set<Vic2::Party, std::function<bool(const Vic2::Party&, const Vic2::Party&)>>
			getParties() const { return parties; }
		std::map<int, HoI4::State*> getStates() const { return states; }
		bool isInFaction() const { return faction != nullptr; }
		bool isCivilized() const { return civilized; }
		int getTechnologyCount() const { return technologies->getTechnologyCount(); }
		bool hasProvinces() const { return provinceCount > 0; }
		bool isGreatPower() const { return greatPower; }
		std::string getCommonCountryFile() const { return commonCountryFile; }
		ConverterColor::Color getColor() const { return color; }
		std::string getFilename() const { return filename; }
		const HoI4::technologies& getTechnologies() const { return *technologies; }
		const HoI4::Army& getArmy() const { return theArmy; }
		const std::vector<HoI4Airplane>& getPlanes() const { return planes; }
		const HoI4::Navies& getNavies() const { return *theNavies; }
		const std::string& getGraphicalCulture() const { return graphicalCulture; }
		const std::string& getGraphicalCulture2d() const { return graphicalCulture2d; }
		bool getGreatPower() const { return greatPower; }
		bool getCivilized() const { return civilized; }
		double getThreat() const { return threat; }
		const std::vector<HoI4::War>& getWars() const { return wars; }
		int getConvoys() const { return convoys; }
		const std::map<std::string, int>& getEquipmentStockpile() const { return equipmentStockpile; }
		const date& getLastElection() const { return lastElection; }
		const std::shared_ptr<HoI4FocusTree> getNationalFocus() const { return nationalFocus; }
		bool isMajorNation() const { return majorNation; }
		const std::set<std::string>& getIdeas() const { return ideas; }
		const std::string& getMobilizationLaw() const { return mobilizationLaw; }
		const std::string& getEconomicLaw() const { return economicLaw; }
		const std::string& getTradeLaw() const { return tradeLaw; }
		int getStability() const { return stability; }
		int getWarSupport() const { return warSupport; }
		const std::string& getLeaderIdeology() const { return leaderIdeology; }
		const std::vector<HoI4::General>& getGenerals() const { return generals; }
		const std::vector<HoI4::Admiral>& getAdmirals() const { return admirals; }
		const HoI4::shipVariants& getTheShipVariants() const { return *theShipVariants; }
		double getMilitaryFactories() const { return militaryFactories; }
		double getCivilianFactories() const { return civilianFactories; }
		double getDockyards() const { return dockyards; }

		std::set<std::string>& editAllies() { return allies; }

	private:
		Country(const Country&) = delete;
		Country& operator=(const Country&) = delete;

		void determineFilename();
		void initIdeas(HoI4::namesMapper& theNames);
		void convertLaws();
		void convertLeaders(const graphicsMapper& theGraphics);
		void convertRelations(const CountryMapper& countryMap);
		void convertWars(const Vic2::Country& sourceCountry, const CountryMapper& countryMap);
		void determineCapitalFromVic2(
			const std::map<int, int>& provinceToStateIDMap,
			const std::map<int, HoI4::State*>& states
		);
		bool isStateValidForCapital(int capitalState, const std::map<int, HoI4::State*>& states);
		bool isThisStateOwnedByUs(const HoI4::State* state) const;
		bool isThisStateACoreWhileWeOwnNoStates(const HoI4::State* state) const;
		void setCapitalInCapitalState(int capitalProvince);
		void findBestCapital();
		void addProvince(int _province);

		const Vic2::Country* srcCountry = nullptr;
		std::string filename;

		bool human = false;

		std::string governmentIdeology = "neutrality";
		std::string leaderIdeology = "conservatism_neutral";
		Vic2::Party rulingParty;
		std::set<Vic2::Party, std::function<bool(const Vic2::Party&, const Vic2::Party&)>> parties;
		std::map<std::string, int> ideologySupport;
		date lastElection;

		std::string sphereLeader;
		std::string tag;
		std::set<int> provinces;
		std::map<int, HoI4::State*> states;
		int capitalStateNum = 0;
		HoI4::State* capitalState = nullptr;
		std::string commonCountryFile;

		std::unique_ptr<HoI4::technologies> technologies;

		std::map<std::string, HoI4Relations*> relations;
		ConverterColor::Color color;
		int stability = 50;
		int warSupport = 50;
		std::shared_ptr<const HoI4Faction> faction;
		std::set<std::string> allies;
		std::set<std::string> puppets;
		std::string puppetMaster;
		std::string graphicalCulture = "western_european_gfx";
		std::string graphicalCulture2d = "western_european_2d";
		bool majorNation = false;
		bool civilized = false;
		int convoys = 0;

		int provinceCount = 0;
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

}



#endif	// HoI4COUNTRY_H_