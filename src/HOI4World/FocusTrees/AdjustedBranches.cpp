#include "AdjustedBranches.h"
#include "external/common_items/Log.h"



HoI4::AdjustedBranches::AdjustedBranches(std::map<std::string, std::shared_ptr<Country>> countries,
		HoI4FocusTree& genericFocusTree,
		OnActions& onActions)
{
	Log(LogLevel::Info) << "\tAdding adjusted focus branches";
	for (auto [tag, country]: countries)
	{
		if (genericFocusTree.getBranches().contains("uk_colonial_focus") && country->isGreatPower() &&
			 country->getDominionTag("south_asia"))
		{
			country->addGlobalEventTarget("uk_colonial_focus_ENG");
			country->addFocusTreeBranch("uk_colonial_focus", onActions);
			genericFocusTree.eraseBranch("uk_colonial_focus");
			branchNames.push_back("uk_colonial_focus");
		}
		if (genericFocusTree.getBranches().contains("FRA_begin_rearmament") && country->isHuman())
		{
			country->addGlobalEventTarget("FRA_begin_rearmament_FRA");
			country->addFocusTreeBranch("FRA_begin_rearmament", onActions);
			branchNames.push_back("FRA_begin_rearmament");
		}
	}
}