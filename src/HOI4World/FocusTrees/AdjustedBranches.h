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
		 OnActions& onActions,
		 const HoI4::MapUtils& mapUtils,
		 const std::map<int, int>& provinceToStateIdMapping,
		 const Maps::MapData& theMapData,
		 const Maps::ProvinceDefinitions& provinceDefinitions);
	std::vector<std::shared_ptr<Country>> sortCountriesByStrength(
		 const std::map<std::string, std::shared_ptr<Country>>& countries);

	[[nodiscard]] const auto& getBranchNames() const { return branchNames; }

  private:
	std::vector<std::string> branchNames;
};

} // namespace HoI4



#endif // ADJUSTED_BRANCHES_