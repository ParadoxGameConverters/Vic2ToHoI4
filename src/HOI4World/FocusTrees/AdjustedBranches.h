#ifndef ADJUSTED_BRANCHES_
#define ADJUSTED_BRANCHES_ value


#include "src/HOI4World/HoI4Country.h"



namespace HoI4
{

class AdjustedBranches
{
  public:
	AdjustedBranches(std::map<std::string, std::shared_ptr<Country>> countries,
		HoI4FocusTree& genericFocusTree,
		OnActions& onActions);

	[[nodiscard]] const auto& getBranchNames() const { return branchNames; }

private:
	std::vector<std::string> branchNames;
};

} // namespace HoI4



#endif // ADJUSTED_BRANCHES_