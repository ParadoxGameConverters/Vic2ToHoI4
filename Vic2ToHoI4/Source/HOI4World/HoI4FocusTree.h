#ifndef HOI4_FOCUS_TREE
#define HOI4_FOCUS_TREE



#include "Date.h"
#include "Diplomacy/HoI4AIStrategy.h"
#include "Events/Events.h"
#include "OnActions.h"
#include "Parser.h"
#include "States/HoI4State.h"
#include <memory>
#include <set>
#include <string>
#include <vector>



class HoI4Focus;


namespace HoI4
{

class Country;
class Events;
class Localisation;
class SharedFocus;
class World;

} // namespace HoI4



class HoI4FocusTree: commonItems::parser
{
  public:
	explicit HoI4FocusTree(const HoI4::Country& country);

	HoI4FocusTree() = default;
	HoI4FocusTree(const HoI4FocusTree&) = default;
	HoI4FocusTree& operator=(const HoI4FocusTree&) = default;
	HoI4FocusTree(HoI4FocusTree&&) = default;
	HoI4FocusTree& operator=(HoI4FocusTree&&) = default;
	~HoI4FocusTree() = default;

	std::unique_ptr<HoI4FocusTree> makeCustomizedCopy(const HoI4::Country& country) const;
	void setNextFreeColumn(int newFreeColumn) { nextFreeColumn = newFreeColumn; }

	void addGenericFocusTree(const std::set<std::string>& majorIdeologies);

	void addDemocracyNationalFocuses(std::shared_ptr<HoI4::Country> Home,
		 std::vector<std::shared_ptr<HoI4::Country>>& CountriesToContain,
		 HoI4::Localisation& hoi4Localisations);
	void addAbsolutistEmpireNationalFocuses(std::shared_ptr<HoI4::Country> country,
		 const std::vector<std::shared_ptr<HoI4::Country>>& targetColonies,
		 const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets,
		 HoI4::Localisation& hoi4Localisations);
	void addCommunistCoupBranch(std::shared_ptr<HoI4::Country> Home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& coupTargets,
		 const std::set<std::string>& majorIdeologies,
		 HoI4::Localisation& hoi4Localisations);
	void addCommunistWarBranch(std::shared_ptr<HoI4::Country> Home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& warTargets,
		 HoI4::Events& events,
		 HoI4::Localisation& hoi4Localisations);
	void addFascistAnnexationBranch(std::shared_ptr<HoI4::Country> Home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets,
		 HoI4::Events& events,
		 HoI4::Localisation& hoi4Localisations);
	void addFascistSudetenBranch(std::shared_ptr<HoI4::Country> Home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& sudetenTargets,
		 const std::vector<std::vector<int>>& demandedStates,
		 HoI4::World& world,
		 HoI4::Localisation& hoi4Localisations);
	void addGPWarBranch(std::shared_ptr<HoI4::Country> Home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& newAllies,
		 const std::vector<std::shared_ptr<HoI4::Country>>& GCTargets,
		 const std::string& ideology,
		 HoI4::Events& events,
		 HoI4::Localisation& hoi4Localisations);
	int getMaxConquerValue(const std::vector<HoI4::AIStrategy>& conquerStrategies);
	std::map<std::string, int> addReconquestBranch(std::shared_ptr<HoI4::Country> theCountry,
		 int& numWarsWithNeighbors,
		 const std::set<std::string>& majorIdeologies,
		 const std::map<int, HoI4::State>& states,
		 HoI4::Localisation& hoi4Localisations
	);
	std::set<std::string> addConquerBranch(
		std::shared_ptr<HoI4::Country> theCountry,
		 int& numWarsWithNeighbors,
		 const std::set<std::string>& majorIdeologies,
		 const std::map<std::string, int>& coreHolders,
		 HoI4::Localisation& hoi4Localisations);
	void addNeighborWarBranch(const std::string& tag,
		 const std::shared_ptr<HoI4::Country>& targetNeighbors,
		 const std::string& targetName,
		 const date& startDate,
		 const std::set<std::string>& majorIdeologies,
		 HoI4::Localisation& hoi4Localisations);
	void addIntegratePuppetsBranch(const std::string& tag,
		 const std::set<std::string>& puppetTags,
		 HoI4::Localisation& hoi4Localisations);
	std::map<std::string, int> determineEnemyCoreHolders(std::shared_ptr<HoI4::Country> theCountry,
		 const std::map<int, HoI4::State>& states);
	int calculateNumEnemyOwnedCores(std::shared_ptr<HoI4::Country> theCountry,
		const std::map<int, HoI4::State>& states);
	void removeFocus(const std::string& id);

	void addFocus(std::shared_ptr<HoI4Focus> newFocus) { focuses.push_back(newFocus); }

	[[nodiscard]] const auto& getDestinationCountryTag() const { return dstCountryTag; }
	[[nodiscard]] const auto& getFocuses() const { return focuses; }
	[[nodiscard]] const auto& getSharedFocuses() const { return sharedFocuses; }
	[[nodiscard]] const auto& getBranches() const { return branches; }

	void addBranch(const std::string& tag, const std::string& branch, HoI4::OnActions& onActions);
	void eraseBranch(const std::string& branch) { branches.erase(branch); }

  private:
	void confirmLoadedFocuses();
	void loadFocuses(const std::string& branch);
	void createBranches();
	std::set<std::string> extractIds(const std::string& prerequisiteStr);
	void addChildrenToBranch(const std::string& head, const std::string& id, int branchLevel);

	size_t calculateNumCollectovistIdeologies(const std::set<std::string>& majorIdeologies);
	void determineMutualExclusions(const std::set<std::string>& majorIdeologies);
	void addFascistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies);
	void addCommunistGenericFocuses(int relativePosition);
	void addAbsolutistGenericFocuses(int relativePosition);
	void addRadicalGenericFocuses(int relativePosition);

	std::string dstCountryTag;
	std::vector<std::shared_ptr<HoI4Focus>> focuses;
	std::vector<std::shared_ptr<HoI4::SharedFocus>> sharedFocuses;
	std::map<std::string, std::map<std::string, int>> branches; // <first focus, all focuses>
	int nextFreeColumn = 0;

	std::string fascistMutualExlusions;
	std::string communistMutualExclusions;
	std::string absolutistMutualExlusions;
	std::string radicalMutualExclusions;
};



#endif // HOI4_FOCUS_TREE