#ifndef HOI4_ONACTIONS_H
#define HOI4_ONACTIONS_H



#include <map>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class OnActions
{
  public:
	OnActions() noexcept;

	void addElectionEvent(const std::string& electionEvent) { electionEvents.push_back(electionEvent); }
	void addFocusEvent(const std::string& tag, const std::string& focusId) { focusEvents[tag] = focusId; }
	void addUnbuiltCanal(const std::string& canal) { unbuiltCanals.insert(canal); }

	[[nodiscard]] const auto& getElectionEvents() const { return electionEvents; }
	[[nodiscard]] const auto& getFocusEvents() const { return focusEvents; }
	[[nodiscard]] const auto& getUnbuiltCanals() const { return unbuiltCanals; }

  private:
	OnActions(const OnActions&) = delete;
	OnActions& operator=(const OnActions&) = delete;

	std::vector<std::string> electionEvents;
	std::map<std::string, std::string> focusEvents;
	std::set<std::string> unbuiltCanals;
};

} // namespace HoI4



#endif // HOI4_ONACTIONS_H
