#ifndef HoI4COUNTRY_H_
#define HoI4COUNTRY_H_



#include "HoI4Airforce.h"
#include "HoI4Army.h"
#include "HoI4Faction.h"
#include "HoI4FocusTree.h"
#include "HOI4Ideology.h"
#include "HoI4Leader.h"
#include "HoI4Relations.h"
#include "HoI4War.h"
#include "Navies/Navies.h"
#include "ShipTypes/ShipVariants.h"
#include "Technologies.h"
#include "../Color.h"
#include "Date.h"
#include "../V2World/Party.h"
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>



namespace Vic2
{
class Country;
class World;
}


class HoI4Ideology;


namespace HoI4
{
class coastalProvinces;
class MtgUnitMappings;
class namesMapper;
class ShipVariant;
class State;
class UnitMappings;
}


namespace mappers
{
class FlagsToIdeasMapper;
class techMapper;
}


class CountryMapper;
class governmentMapper;
class graphicsMapper;


class Date;



namespace HoI4
{

class Country
{
	public:
		explicit Country(
			const std::string& _tag,
			const Vic2::World& _srcWorld,
			const Vic2::Country* _srcCountry,
			const std::map<int, int>& stateMap,
			const std::map<int, HoI4::State>& states,
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
			const std::map<int, int>& provinceToStateIDMap,
			const std::map<int, HoI4::State>& allStates
		);
		void convertConvoys(const HoI4::UnitMappings& unitMap);
		void convertAirforce(const HoI4::UnitMappings& unitMap);
		void convertArmies(const HoI4::militaryMappings& theMilitaryMappings);
		void convertTechnology(std::unique_ptr<mappers::techMapper>& theTechMapper);
		void addState(const HoI4::State& state);
		void calculateIndustry(const std::map<int, HoI4::State>& allStates);
		void addGenericFocusTree(const std::set<std::string>& majorIdeologies);
		void adjustResearchFocuses();

		void setSphereLeader(const std::string& SphereLeader) { sphereLeader = SphereLeader; }
		void setFaction(std::shared_ptr<const HoI4Faction> newFaction) { faction = newFaction; }
		void giveNationalFocus(std::unique_ptr<HoI4FocusTree>& NF) { nationalFocus = std::move(NF); }
		void setGreatPower() { greatPower = true; }
		void setPuppetmaster(const std::string& _master) { puppetMaster = _master; }
		void addPuppet(const std::string& countryTag) { puppets.insert(countryTag); }

		std::optional<HoI4Relations> getRelations(std::string withWhom) const;
		double getStrengthOverTime(double years) const;
		double getMilitaryStrength() const;
		double getEconomicStrength(double years) const;
		bool areElectionsAllowed() const;
		std::optional<HoI4Faction> getFaction() const;
		std::optional<HoI4FocusTree> getNationalFocus() const;

		const std::string& getTag() const { return tag; }
		const Vic2::Country& getSourceCountry() const { return sourceCountry; }
		const std::string& getFilename() const { return filename; }
		const std::string& getCommonCountryFile() const { return commonCountryFile; }
		bool isHuman() const { return human; }

		const ConverterColor::Color& getColor() const { return color; }
		const std::string& getGraphicalCulture() const { return graphicalCulture; }
		const std::string& getGraphicalCulture2d() const { return graphicalCulture2d; }

		bool hasProvinces() const { return provinces.size() > 0; }
		const std::set<int>& getProvinces() const { return provinces; }
		const std::set<int>& getStates() const { return states; }
		int getCapitalStateNum() const { return capitalState; }
		std::optional<int> getCapitalProvince() const { return capitalProvince; }

		const std::string& getGovernmentIdeology() const { return governmentIdeology; }
		const std::string& getLeaderIdeology() const { return leaderIdeology; }
		const Vic2::Party& getRulingParty() const { return rulingParty; }
		const std::set<Vic2::Party, std::function<bool(const Vic2::Party&, const Vic2::Party&)>>&
			getParties() const { return parties; }
		const std::map<std::string, int>& getIdeologySupport() const { return ideologySupport; }
		const date& getLastElection() const { return lastElection; }
		int getStability() const { return stability; }
		int getWarSupport() const { return warSupport; }
		const std::string& getMobilizationLaw() const { return mobilizationLaw; }
		const std::string& getEconomicLaw() const { return economicLaw; }
		const std::string& getTradeLaw() const { return tradeLaw; }

		int getTechnologyCount() const { return technologies->getTechnologyCount(); }
		const HoI4::technologies& getTechnologies() const { return *technologies; }
		const std::set<std::string>& getIdeas() const { return ideas; }

		double getMilitaryFactories() const { return militaryFactories; }
		double getCivilianFactories() const { return civilianFactories; }
		double getDockyards() const { return dockyards; }

		const HoI4::Army& getArmy() const { return theArmy; }
		const HoI4::shipVariants& getTheShipVariants() const { return *theShipVariants; }
		const HoI4::Navies& getNavies() const { return *theNavies; }
		int getConvoys() const { return convoys; }
		const std::vector<HoI4Airplane>& getPlanes() const { return planes; }
		const std::map<std::string, int>& getEquipmentStockpile() const { return equipmentStockpile; }
		const std::vector<HoI4::General>& getGenerals() const { return generals; }
		const std::vector<HoI4::Admiral>& getAdmirals() const { return admirals; }

		const std::map<std::string, HoI4Relations>& getRelations() const { return relations; }
		const std::vector<HoI4::War>& getWars() const { return wars; }
		double getThreat() const { return threat; }
		bool isInFaction() const { return faction.operator bool(); }
		const std::string& getSphereLeader() const { return sphereLeader; }
		const std::set<std::string>& getAllies() const { return allies; }
		const std::set<std::string>& getPuppets() const { return puppets; }
		const std::string& getPuppetmaster() const { return puppetMaster; }
		bool isGreatPower() const { return greatPower; }
		bool isCivilized() const { return civilized; }

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
			const std::map<int, int>& provinceTosIDMap,
			const std::map<int, HoI4::State>& states
		);

		bool isStateValidForCapital(int capitalState, const std::map<int, HoI4::State>& states);
		bool isThisStateOwnedByUs(const HoI4::State& state) const;
		bool isThisStateACoreWhileWeOwnNoStates(const HoI4::State& state) const;

		void findBestCapital();
		void addProvince(int _province);

		std::string tag;
		const Vic2::Country& sourceCountry;
		std::string filename;
		std::string commonCountryFile;
		bool human = false;

		ConverterColor::Color color;
		std::string graphicalCulture = "western_european_gfx";
		std::string graphicalCulture2d = "western_european_2d";

		std::set<int> provinces;
		std::set<int> states;
		int capitalState = 0;
		std::optional<int> capitalProvince;

		std::string governmentIdeology = "neutrality";
		std::string leaderIdeology = "conservatism_neutral";
		Vic2::Party rulingParty;
		std::set<Vic2::Party, std::function<bool(const Vic2::Party&, const Vic2::Party&)>> parties;
		std::map<std::string, int> ideologySupport;
		date lastElection;
		int stability = 50;
		int warSupport = 50;
		std::string mobilizationLaw = "volunteer_only";
		std::string economicLaw = "civilian_economy";
		std::string tradeLaw = "export_focus";

		std::unique_ptr<HoI4::technologies> technologies;
		std::set<std::string> ideas;
		std::unique_ptr<HoI4FocusTree> nationalFocus;

		double militaryFactories = 0.0;
		double civilianFactories = 0.0;
		double dockyards = 0.0;

		HoI4::Army theArmy;
		std::unique_ptr<HoI4::shipVariants> theShipVariants;
		std::unique_ptr<HoI4::Navies> theNavies;
		int convoys = 0;
		std::vector<HoI4Airplane> planes;
		std::map<std::string, int> equipmentStockpile;
		std::vector<HoI4::General> generals;
		std::vector<HoI4::Admiral> admirals;

		std::map<std::string, HoI4Relations> relations;
		std::vector<HoI4::War> wars;
		double threat = 0.0;
		std::shared_ptr<const HoI4Faction> faction;
		std::string sphereLeader;
		std::set<std::string> allies;
		std::set<std::string> puppets;
		std::string puppetMaster;
		bool greatPower = false;
		bool civilized = false;
};

}



#endif	// HoI4COUNTRY_H_