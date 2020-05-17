#ifndef HOI4_STATES_H
#define HOI4_STATES_H



#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "../Map/StrategicRegions.h"
#include "DefaultState.h"
#include "Parser.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include "../Map/MapData.h"
#include "../Map/Hoi4Province.h"



class Configuration;
class CountryMapper;



namespace Vic2
{
class Localisations;
class StateDefinitions;
class Country;
class Province;
class State;
class World;
} // namespace Vic2


namespace HoI4
{

class Country;
class CoastalProvinces;
class ImpassableProvinces;
class Localisation;
class ProvinceDefinitions;
class State;


class States: commonItems::parser
{
  public:
	States() = default;
	explicit States(const Vic2::World* sourceWorld,
		 const CountryMapper& countryMap,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const StrategicRegions& strategicRegions,
		 const Vic2::Localisations& vic2Localisations,
		 const ProvinceDefinitions& provinceDefinitions,
		 const MapData& mapData,
		 Localisation& hoi4Localisations,
		 const mappers::ProvinceMapper& provinceMapper,
		 const Configuration& theConfiguration);

	const std::map<int, HoI4::DefaultState>& getDefaultStates() const { return defaultStates; }
	const std::map<int, HoI4::State>& getStates() const { return states; }
	const std::map<int, int>& getProvinceToStateIDMap() const { return provinceToStateIDMap; }

	void convertAirBases(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
		 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers);
	void convertResources();
	void putIndustryInStates(const std::map<std::string, double>& factoryWorkerRatios,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Configuration& theConfiguration);
	void convertCapitalVPs(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
		 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
		 double greatestStrength);
	void addCapitalsToStates(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);

  private:
	void determineOwnersAndCores(const CountryMapper& countryMap,
		 const Vic2::World& sourceWorld,
		 const ProvinceDefinitions& provinceDefinitions,
		 const mappers::ProvinceMapper& provinceMapper);
	std::optional<std::vector<int>> retrieveSourceProvinceNums(int provNum,
		 const mappers::ProvinceMapper& provinceMapper) const;
	const std::map<std::string, std::pair<int, int>> determinePotentialOwners(const std::vector<int>& sourceProvinceNums,
		 const Vic2::World& sourceWorld) const;
	const std::string selectProvinceOwner(const std::map<std::string, std::pair<int, int>>& potentialOwners) const;
	std::set<std::string> determineCores(const std::vector<int>& sourceProvinces,
		 const std::string& Vic2Owner,
		 const CountryMapper& countryMap,
		 const std::string& newOwner,
		 const Vic2::World& sourceWorld) const;

	void createStates(const std::map<std::string, Vic2::Country*>& sourceCountries,
		 const std::map<int, Vic2::Province*>& sourceProvinces,
		 const HoI4::ImpassableProvinces& theImpassableProvinces,
		 const CountryMapper& countryMap,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const StrategicRegions& strategicRegions,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations,
		 const mappers::ProvinceMapper& provinceMapper,
		 const MapData& mapData,
		 const Configuration& theConfiguration);
	void createMatchingHoI4State(const Vic2::State* vic2State,
		 const std::string& stateOwner,
		 const HoI4::ImpassableProvinces& theImpassableProvinces,
		 const CountryMapper& countryMapper,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const StrategicRegions& strategicRegions,
		 const Vic2::Localisations& vic2Localisations,
		 Localisation& hoi4Localisations,
		 const mappers::ProvinceMapper& provinceMapper,
		 const MapData& mapData,
		 const std::map<int, Province>& provinces,
		 const Configuration& theConfiguration);
	std::set<int> getProvincesInState(const Vic2::State* vic2State,
		 const std::string& owner,
		 const mappers::ProvinceMapper& provinceMapper);
	std::vector<std::set<int>> getConnectedProvinceSets(std::set<int> provinceNumbers,
		 const MapData& mapData,
		 const std::map<int, Province>& provinces);
	std::vector<std::set<int>> consolidateProvinceSets(std::vector<std::set<int>> connectedProvinceSets,
		 const std::map<int, int>& provinceToStrategicRegionMap);
	void addProvincesAndCoresToNewState(HoI4::State& newState, const std::set<int>& provinces);
	bool isProvinceValid(int provNum) const;
	bool isProvinceOwnedByCountry(int provNum, const std::string& stateOwner) const;
	bool isProvinceNotAlreadyAssigned(int provNum) const;
	unsigned int getTotalManpower() const;

	void addBasicAirBases();
	void addCapitalAirBases(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
	void addGreatPowerAirBases(const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers);

	void addBasicCapitalVPs(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
	void addGreatPowerVPs(const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers);
	void addStrengthVPs(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries, double greatestStrength);
	int calculateStrengthVPs(const HoI4::Country& country, double greatestStrength) const;

	std::map<int, std::string> ownersMap;
	std::map<int, std::set<std::string>> coresMap;
	std::set<int> assignedProvinces;

	std::map<int, HoI4::DefaultState> defaultStates;
	std::map<int, HoI4::State> states;
	std::map<int, int> provinceToStateIDMap;
	int nextStateID = 1;
};

} // namespace HoI4



#endif // HOI4_STATES_H
