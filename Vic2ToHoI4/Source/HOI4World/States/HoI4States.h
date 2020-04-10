#ifndef HOI4_STATES_H
#define HOI4_STATES_H



#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "DefaultState.h"
#include "newParser.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>


class V2Localisations;
class CountryMapper;


namespace Vic2
{
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
class State;


class States: commonItems::parser
{
  public:
	States() = default;
	explicit States(const Vic2::World* sourceWorld,
		 const CountryMapper& countryMap,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const V2Localisations& vic2Localisations);

	const std::map<int, HoI4::DefaultState>& getDefaultStates() const { return defaultStates; }
	const std::map<int, HoI4::State>& getStates() const { return states; }
	const std::map<int, int>& getProvinceToStateIDMap() const { return provinceToStateIDMap; }

	void convertAirBases(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
		 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers);
	void convertResources();
	void putIndustryInStates(const std::map<std::string, double>& factoryWorkerRatios,
		 const HoI4::CoastalProvinces& theCoastalProvinces);
	void convertCapitalVPs(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
		 const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
		 double greatestStrength);
	void addCapitalsToStates(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);

  private:
	void determineOwnersAndCores(const CountryMapper& countryMap, const Vic2::World& sourceWorld);
	std::optional<std::vector<int>> retrieveSourceProvinceNums(int provNum) const;
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
		 const HoI4::ImpassableProvinces& theImpassables,
		 const CountryMapper& countryMap,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const V2Localisations& vic2Localisations);
	void createMatchingHoI4State(const Vic2::State* vic2State,
		 const std::string& stateOwner,
		 const HoI4::ImpassableProvinces& theImpassables,
		 const CountryMapper& countryMapper,
		 const HoI4::CoastalProvinces& theCoastalProvinces,
		 const Vic2::StateDefinitions& theStateDefinitions,
		 const V2Localisations& vic2Localisations);
	std::set<int> getProvincesInState(const Vic2::State* vic2State, const std::string& owner);
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
