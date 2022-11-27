#ifndef ADJUSTED_BRANCHES_
#define ADJUSTED_BRANCHES_ value


#include "src/HOI4World/HoI4Country.h"



namespace HoI4
{

class MapUtils;

class AdjustedBranches
{
  public:
	AdjustedBranches(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 HoI4FocusTree& genericFocusTree,
		 OnActions& onActions,
		 const HoI4::MapUtils& mapUtils,
		 const std::map<int, int>& provinceToStateIdMapping,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 Character::Factory& characterFactory);

	void addUKColonialFocusBranch(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 HoI4FocusTree& genericFocusTree,
		 OnActions& onActions);
	void addBeginRearmamentBranch(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 HoI4FocusTree& genericFocusTree,
		 OnActions& onActions,
		 Character::Factory& characterFactory);

	[[nodiscard]] const auto& getBranchNames() const { return branchNames; }

  private:
	void determineGPZonesOfAccess(const std::vector<std::shared_ptr<Country>>& greatPowers,
		 const std::map<std::string, std::shared_ptr<Country>>& theCountries);
	void addCountriesToGPZoneOfAccess(const std::shared_ptr<Country>& gp,
		 const std::shared_ptr<Country>& referenceCountry,
		 const std::map<std::string, std::shared_ptr<Country>>& countries);
	void addToGPZoneOfAccess(const std::shared_ptr<Country>& gp,
		 const std::shared_ptr<Country>& country,
		 const std::map<std::string, std::shared_ptr<Country>>& countries);

	std::vector<std::shared_ptr<Country>> sortCountriesByStrength(
		 const std::map<std::string, std::shared_ptr<Country>>& countries);
	bool countriesShareBorder(const std::shared_ptr<Country>& country, const std::shared_ptr<Country>& attacker);
	bool attackerCanPositionTroopsOnCountryBorders(const std::shared_ptr<Country>& country,
		 const std::string& attackerTag,
		 const std::map<std::string, std::shared_ptr<Country>>& countries);
	void flagZoneOfAccess(const std::string& gpTag,
		 const std::string& flag,
		 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries);
	void importCharacters(std::shared_ptr<Country> country, std::string_view filename, Character::Factory& characterFactory);
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> getNeighbors(const std::shared_ptr<Country>& country,
		 const std::map<std::string, std::shared_ptr<Country>>& countries);

	std::vector<std::string> branchNames;
	std::map<std::string, std::set<std::string>> gpZonesOfAccess; // great power, contiguous countries GP can access

	const HoI4::MapUtils& mapUtils;
	const std::map<int, int>& provinceToStateIdMapping;
	const Maps::MapData& theMapData;
	const Maps::ProvinceDefinitions& provinceDefinitions;
};

} // namespace HoI4



#endif // ADJUSTED_BRANCHES_