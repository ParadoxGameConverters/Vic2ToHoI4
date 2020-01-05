#ifndef HOI4_STATES_H
#define HOI4_STATES_H



#include "../../Mappers/Provinces/ProvinceMapper.h"
#include "newParser.h"
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>



class CountryMapper;
namespace HoI4
{
class Country;
class coastalProvinces;
class DefaultState;
class impassableProvinces;
class State;
}
namespace Vic2
{
class Country;
class State;
class World;
}



class HoI4States: commonItems::parser
{
	public:
		explicit HoI4States(const Vic2::World* _sourceWorld, const CountryMapper& countryMap);

		const std::map<int, HoI4::DefaultState>& getDefaultStates() const { return defaultStates; }
		const std::map<int, HoI4::State>& getStates() const { return states; }
		const std::map<int, int>& getProvinceToStateIDMap() const { return provinceToStateIDMap; }

		void convertAirBases(
			const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
			const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers
		);
		void convertResources();
		void putIndustryInStates(
			const std::map<std::string, double>& factoryWorkerRatios,
			const HoI4::coastalProvinces& theCoastalProvinces
		);
		void convertNavalBases(const HoI4::coastalProvinces& theCoastalProvinces);
		void convertCapitalVPs(
			const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
			const std::vector<std::shared_ptr<HoI4::Country>>& greatPowers,
			double greatestStrength
		);
		void addCapitalsToStates(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);

	private:
		void determineOwnersAndCores(const CountryMapper& countryMap);
		std::optional<std::vector<int>> retrieveSourceProvinceNums(int provNum) const;
		const std::map<std::string, std::pair<int, int>> determinePotentialOwners(
			const std::vector<int>& sourceProvinceNums
		) const;
		const std::string selectProvinceOwner(const std::map<std::string, std::pair<int, int>>& potentialOwners) const;
		std::set<std::string> determineCores(
			const std::vector<int>& sourceProvinces,
			const std::string& Vic2Owner,
			const CountryMapper& countryMap,
			const std::string& newOwner
		) const;

		void createStates(const HoI4::impassableProvinces& theImpassables, const CountryMapper& countryMap);
		void createMatchingHoI4State(
			const Vic2::State* vic2State,
			const std::string& stateOwner,
			const HoI4::impassableProvinces& theImpassables,
			const CountryMapper& countryMapper
		);
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
		void addStrengthVPs(
			const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
			double greatestStrength
		);
		int calculateStrengthVPs(const HoI4::Country& country, double greatestStrength) const;


		const Vic2::World* sourceWorld = nullptr;
		std::map<int, std::string> ownersMap;
		std::map<int, std::set<std::string>> coresMap;
		std::set<int> assignedProvinces;

		std::map<int, HoI4::DefaultState> defaultStates;
		std::map<int, HoI4::State> states;
		std::map<int, int> provinceToStateIDMap;
		int nextStateID = 1;
};



#endif // HOI4_STATES_H
