#ifndef ADJUSTED_BRANCHES_
#define ADJUSTED_BRANCHES_ value


#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/Ideas/Ideas.h"



namespace HoI4
{

class MapUtils;

class AdjustedBranches
{
  public:
	AdjustedBranches(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 const std::set<std::string>& majorIdeologies,
		 OnActions& onActions,
		 const HoI4::MapUtils& mapUtils,
		 const std::map<int, int>& provinceToStateIdMapping,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions,
		 Character::Factory& characterFactory,
		 Ideas& ideas);

	void addUKColonialFocusBranch(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 const std::set<std::string>& majorIdeologies,
		 OnActions& onActions,
		 Ideas& ideas);
	void addBeginRearmamentBranch(const std::map<std::string, std::shared_ptr<Country>>& countries,
		 OnActions& onActions,
		 Character::Factory& characterFactory,
		 Ideas& ideas,
		 const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getAddedBranches() const { return addedBranches; }

  private:
	HoI4FocusTree createBranch(const std::string& name, const std::set<std::string>& majorIdeologies);
	void updateAdjustedFocuses(HoI4FocusTree& focusTree, const std::set<std::string>& majorIdeologies);

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
	void importCharacters(std::shared_ptr<Country> country,
		 const std::string& branch,
		 Character::Factory& characterFactory);
	[[nodiscard]] std::map<std::string, std::shared_ptr<Country>> getNeighbors(const std::shared_ptr<Country>& country,
		 const std::map<std::string, std::shared_ptr<Country>>& countries);

	void addIdeas(const std::string& branch, Ideas& ideas, const std::set<std::string>& majorIdeologies);

	std::vector<std::string> addedBranches;
	std::map<std::string, std::set<std::string>> gpZonesOfAccess; // great power, contiguous countries GP can access

	const HoI4::MapUtils& mapUtils;
	const std::map<int, int>& provinceToStateIdMapping;
	const Maps::MapData& theMapData;
	const Maps::ProvinceDefinitions& provinceDefinitions;
};

} // namespace HoI4



#endif // ADJUSTED_BRANCHES_