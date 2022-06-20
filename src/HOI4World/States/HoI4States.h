#ifndef HOI4_STATES_H
#define HOI4_STATES_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Map/Hoi4Province.h"
#include "src/HOI4World/Map/StrategicRegions.h"
#include "src/HOI4World/Names/Names.h"
#include "src/HOI4World/Regions/Regions.h"
#include "src/HOI4World/States/DefaultState.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/Country/CountryMapperFactory.h"
#include "src/Mappers/Graphics/GraphicsMapper.h"
#include "src/Mappers/Provinces/ProvinceMapper.h"
#include "src/Maps/MapData.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/States/State.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



class Configuration;



namespace Vic2
{
class Localisations;
class StateDefinitions;
class Country;
class Province;
class World;
} // namespace Vic2


namespace HoI4
{

class Country;
class CoastalProvinces;
class ImpassableProvinces;
class Localisation;
class State;


class States: commonItems::parser
{
  public:
	States() = default;
	explicit States(const Vic2::World& sourceWorld,
		 const Mappers::CountryMapper& countryMap,
		 const std::map<int, Province>& theProvinces,
		 const CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const StrategicRegions& strategicRegions,
		 const Vic2::Localisations& vic2Localisations,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 const Maps::MapData& mapData,
		 Localisation& hoi4Localisations,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const ImpassableProvinces& impassableProvinces,
		 const std::map<int, DefaultState>& defaultStates,
		 const Configuration& theConfiguration);

	[[nodiscard]] const std::map<int, DefaultState>& getDefaultStates() const { return defaultStates_; }
	[[nodiscard]] const std::map<int, State>& getStates() const { return states; }
	[[nodiscard]] const std::map<int, int>& getProvinceToStateIDMap() const { return provinceToStateIDMap; }
	[[nodiscard]] const auto& getLanguageCategories() const { return languageCategories; }
	[[nodiscard]] std::map<int, State>& getModifiableStates() { return states; }

	[[nodiscard]] std::set<int> getNavalBaseLocations() const;

	void convertAirBases(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 const std::vector<std::shared_ptr<Country>>& greatPowers);
	void convertResources(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
	void putIndustryInStates(const std::map<std::string, double>& factoryWorkerRatios,
		 const CoastalProvinces& theCoastalProvinces,
		 const Configuration& theConfiguration);
	void convertCapitalVPs(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 const std::vector<std::shared_ptr<Country>>& greatPowers);
	void addCapitalsToStates(const std::map<std::string, std::shared_ptr<Country>>& countries);
	void giveProvinceControlToCountry(int provinceNum,
		 const std::string& country,
		 const std::set<std::string>& ownersToSkip);
	void addCoresToCorelessStates(const std::map<std::string, Vic2::Country>& sourceCountries,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2Provinces,
		 bool debug);

  private:
	void determineOwnersAndCores(const Mappers::CountryMapper& countryMap,
		 const Vic2::World& sourceWorld,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 const Mappers::ProvinceMapper& provinceMapper);
	[[nodiscard]] static std::optional<std::vector<int>> retrieveSourceProvinceNumbers(int provNum,
		 const Mappers::ProvinceMapper& provinceMapper);
	[[nodiscard]] static std::map<std::string, std::pair<int, int>> determinePotentialOwners(
		 const std::vector<int>& sourceProvinceNumbers,
		 const Vic2::World& sourceWorld);
	[[nodiscard]] static std::string selectProvinceOwner(
		 const std::map<std::string, std::pair<int, int>>& potentialOwners);
	[[nodiscard]] static std::set<std::pair<std::string, std::string>> determineCores(
		 const std::vector<int>& sourceProvinces,
		 const std::string& Vic2Owner,
		 const Mappers::CountryMapper& countryMap,
		 const std::string& newOwner,
		 const Vic2::World& sourceWorld);

	void createStates(const std::map<std::string, Vic2::Country>& sourceCountries,
		 const std::map<int, std::shared_ptr<Vic2::Province>>& sourceProvinces,
		 const std::map<int, Province>& theProvinces,
		 const ImpassableProvinces& theImpassableProvinces,
		 const Mappers::CountryMapper& countryMap,
		 const CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const StrategicRegions& strategicRegions,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Maps::MapData& mapData,
		 const ImpassableProvinces& impassableProvinces,
		 const Configuration& theConfiguration);
	void createMatchingHoI4State(const Vic2::State& vic2State,
		 const std::string& stateOwner,
		 const ImpassableProvinces& theImpassableProvinces,
		 const Mappers::CountryMapper& countryMapper,
		 const std::map<std::string, Vic2::Country>& sourceCountries,
		 const CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const StrategicRegions& strategicRegions,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const Maps::MapData& mapData,
		 const std::map<int, Province>& provinces,
		 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2Provinces,
		 const Configuration& theConfiguration,
		 const std::map<std::string, std::string>& grammarMappings,
		 const ImpassableProvinces& impassableProvinces);
	std::set<int> getProvincesInState(const Vic2::State& vic2State,
		 const std::string& owner,
		 const Mappers::ProvinceMapper& provinceMapper);
	static std::vector<std::set<int>> getConnectedProvinceSets(std::set<int> provinceNumbers,
		 const Maps::MapData& mapData,
		 const std::map<int, Province>& provinces);
	static std::vector<std::set<int>> consolidateProvinceSets(std::vector<std::set<int>> connectedProvinceSets,
		 const std::map<int, int>& provinceToStrategicRegionMap);
	void addProvincesAndCoresToNewState(State& newState,
		 const std::map<std::string, Vic2::Country>& sourceCountries,
		 const std::set<int>& provinceNumbers,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2Provinces);
	[[nodiscard]] bool isProvinceOwnedByCountry(int provNum, const std::string& stateOwner) const;
	[[nodiscard]] bool isProvinceNotAlreadyAssigned(int provNum) const;
	[[nodiscard]] unsigned int getTotalManpower() const;

	void addBasicAirBases();
	void addCapitalAirBases(const std::map<std::string, std::shared_ptr<Country>>& countries);
	void addGreatPowerAirBases(const std::vector<std::shared_ptr<Country>>& greatPowers);

	void addGreatPowerVPs(const std::vector<std::shared_ptr<Country>>& greatPowers);
	void addCapitalVictoryPoints(const std::map<std::string, std::shared_ptr<Country>>& countries);

	std::map<int, std::string> ownersMap;
	std::map<int, std::set<std::pair<std::string, std::string>>> coresMap;
	std::set<int> assignedProvinces;

	std::map<int, DefaultState> defaultStates_;
	std::map<int, State> states;
	std::map<int, int> provinceToStateIDMap;
	int nextStateID = 1;

	std::map<std::string, std::set<int>> languageCategories;
};

} // namespace HoI4



#endif // HOI4_STATES_H