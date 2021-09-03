#ifndef HOI4_ONACTIONS_H
#define HOI4_ONACTIONS_H



#include <map>
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
	void addCivilWarEvent(const std::string& tag, const std::string& focusId)
	{
		civilWarEvents.push_back(std::make_pair(tag, focusId));
	}

	[[nodiscard]] const auto& getElectionEvents() const { return electionEvents; }
	[[nodiscard]] const auto& getFocusEvents() const { return focusEvents; }
	[[nodiscard]] const auto& getCivilWarEvents() const { return civilWarEvents; }

  private:
	OnActions(const OnActions&) = delete;
	OnActions& operator=(const OnActions&) = delete;

	std::vector<std::string> electionEvents;
	std::map<std::string, std::string> focusEvents;
	std::vector<std::pair<std::string, std::string>> civilWarEvents;
};

} // namespace HoI4



#endif // HOI4_ONACTIONS_H
