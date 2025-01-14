#ifndef HOI4_FOCUS_TREE
#define HOI4_FOCUS_TREE



#include "external/common_items/ConvenientParser.h"
#include "external/common_items/Date.h"
#include "src/HOI4World/Diplomacy/HoI4AIStrategy.h"
#include "src/HOI4World/Events/Events.h"
#include "src/HOI4World/OnActions.h"
#include "src/HOI4World/States/HoI4State.h"
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

	[[nodiscard]] std::unique_ptr<HoI4FocusTree> makeCustomizedCopy(const HoI4::Country& country) const;
	void setNextFreeColumn(int newFreeColumn) { nextFreeColumn = newFreeColumn; }

	void addGenericFocusTree(const std::set<std::string>& majorIdeologies);

	void addDemocracyNationalFocuses(const HoI4::Country& home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& CountriesToContain,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addAbsolutistEmpireNationalFocuses(const HoI4::Country& home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& targetColonies,
		 const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addCommunistCoupBranch(const HoI4::Country& home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& coupTargets,
		 const std::set<std::string>& majorIdeologies,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addCommunistWarBranch(const HoI4::Country& home,
		 std::vector<std::shared_ptr<HoI4::Country>> warTargets,
		 HoI4::Events& events,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addFascistAnnexationBranch(const HoI4::Country& home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& annexationTargets,
		 const size_t numSudetenTargets,
		 HoI4::Events& events,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addFascistSudetenBranch(const HoI4::Country& home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& anschlussTargets,
		 const std::vector<std::shared_ptr<HoI4::Country>>& sudetenTargets,
		 const std::map<std::string, std::vector<int>>& demandedStates,
		 HoI4::Events& events,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addGPWarBranch(const HoI4::Country& home,
		 const std::vector<std::shared_ptr<HoI4::Country>>& newAllies,
		 const std::vector<std::shared_ptr<HoI4::Country>>& GCTargets,
		 const std::string& ideology,
		 const std::set<std::string>& majorIdeologies,
		 HoI4::Events& events,
		 Mappers::FactionNameMapper& factionNameMapper,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	std::map<std::string, std::set<int>> addReconquestBranch(const HoI4::Country& theCountry,
		 int& numWarsWithNeighbors,
		 const std::set<std::string>& majorIdeologies,
		 const std::map<int, HoI4::State>& states,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	std::set<std::string> addConquerBranch(const HoI4::Country& theCountry,
		 int& numWarsWithNeighbors,
		 const std::set<std::string>& majorIdeologies,
		 const std::map<std::string, std::set<int>>& coreHolders,
		 const std::map<int, HoI4::State>& states,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void addIntegratePuppetsBranch(const std::string& tag,
		 const std::map<std::string, std::string>& puppets,
		 HoI4::Localisation& hoi4Localisations,
		 bool debug);
	void removeFocus(const std::string& id);
	void makeEmpty() { emptyFocusTree = true; }

	void addFocus(std::shared_ptr<HoI4Focus> newFocus) { focuses.push_back(newFocus); }

	[[nodiscard]] const auto& getDestinationCountryTag() const { return dstCountryTag; }
	[[nodiscard]] const auto& getFocuses() const { return focuses; }
	[[nodiscard]] const auto& getSharedFocuses() const { return sharedFocuses; }
	[[nodiscard]] bool isEmpty() const { return emptyFocusTree; }

	std::pair<int, int> calculateBranchSpan(const std::vector<std::shared_ptr<HoI4Focus>>& focuses);
	void addBranch(const std::vector<std::shared_ptr<HoI4Focus>>& adjustedFocuses, HoI4::OnActions& onActions);

  private:
	void confirmLoadedFocuses();

	void addFascistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies);
	void addCommunistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies);
	void addAbsolutistGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies);
	void addRadicalGenericFocuses(int relativePosition, const std::set<std::string>& majorIdeologies);

	std::string dstCountryTag;
	std::vector<std::shared_ptr<HoI4Focus>> focuses;
	std::vector<std::shared_ptr<HoI4::SharedFocus>> sharedFocuses;
	int nextFreeColumn = 0;

	bool emptyFocusTree = false;
};



#endif // HOI4_FOCUS_TREE