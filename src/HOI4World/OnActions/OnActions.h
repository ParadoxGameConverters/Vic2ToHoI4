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
	class Factory;

	OnActions() noexcept;

	void addElectionEvent(const std::string& electionEvent) { electionEvents.push_back(electionEvent); }
	void addFocusEvent(const std::string& tag, const std::string& focusId) { focusEvents[tag] = focusId; }
	void addOnAction(const std::string& key, const std::string& effects) { importedOnActions.emplace(key, effects); }

	[[nodiscard]] const auto& getElectionEvents() const { return electionEvents; }
	[[nodiscard]] const auto& getFocusEvents() const { return focusEvents; }
	[[nodiscard]] const auto& getImportedOnActions() const { return importedOnActions; }

  private:
	OnActions(const OnActions&) = delete;
	OnActions& operator=(const OnActions&) = delete;

	std::vector<std::string> electionEvents;
	std::map<std::string, std::string> focusEvents;
	std::multimap<std::string, std::string> importedOnActions;
};

} // namespace HoI4



#endif // HOI4_ONACTIONS_H
