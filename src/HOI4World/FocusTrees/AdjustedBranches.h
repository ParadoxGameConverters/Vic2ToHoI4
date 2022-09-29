#ifndef ADJUSTED_BRANCHES_
#define ADJUSTED_BRANCHES_ value


#include "src/HOI4World/HoI4Country.h"



namespace HoI4
{

class MapUtils;

class AdjustedBranches
{
  public:
	AdjustedBranches(std::map<std::string, std::shared_ptr<Country>> countries,
		 HoI4FocusTree& genericFocusTree,
		 OnActions& onActions,
		 const HoI4::MapUtils& mapUtils,
		 const std::map<int, int>& provinceToStateIdMapping,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions);

	void addUKColonialFocusBranch(std::map<std::string, std::shared_ptr<Country>> countries,
		 HoI4FocusTree& genericFocusTree,
		 OnActions& onActions);
	void addBeginRearmamentBranch(std::map<std::string, std::shared_ptr<Country>> countries,
		 HoI4FocusTree& genericFocusTree,
		 OnActions& onActions);
	std::vector<std::shared_ptr<Country>> sortCountriesByStrength(
		 const std::map<std::string, std::shared_ptr<Country>>& countries);
	bool countriesShareBorder(const std::shared_ptr<Country>& country, const std::shared_ptr<Country>& attacker);
	bool attackerCanPositionTroopsOnCountryBorders(const std::shared_ptr<Country>& countryOne,
		 const std::shared_ptr<Country>& countryTwo);

	[[nodiscard]] const auto& getBranchNames() const { return branchNames; }

  private:
	void determineGPZonesOfAccess(const std::vector<std::shared_ptr<Country>>& greatPowers,
		 const std::map<std::string, std::shared_ptr<Country>>& theCountries);
	void addToGPZoneOfAccess(const std::shared_ptr<Country>& gp, const std::vector<std::shared_ptr<Country>>& countries);

	[[nodiscard]] const std::vector<std::shared_ptr<HoI4::Country>>& getNeighbors(
		 const std::shared_ptr<Country>& country,
		 const std::map<std::string, std::shared_ptr<Country>>& countries);

	std::vector<std::string> branchNames;

	const HoI4::MapUtils& mapUtils;
	const std::map<int, int>& provinceToStateIdMapping;
	const Maps::MapData& theMapData;
	const Maps::ProvinceDefinitions& provinceDefinitions;
};

} // namespace HoI4



#endif // ADJUSTED_BRANCHES_