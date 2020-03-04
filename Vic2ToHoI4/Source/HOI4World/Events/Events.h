#ifndef HOI4_EVENTS_H
#define HOI4_EVENTS_H



#include "../../Configuration.h"
#include "../../V2World/Party.h"
#include "Event.h"
#include "newParser.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class OnActions;
class Country;

class Events: commonItems::parser
{
  public:
	Events() = default;
	virtual ~Events() = default;
	Events(const Events&) = default;
	Events(Events&&) = default;
	Events& operator=(const Events&) = default;
	Events& operator=(Events&&) = default;

	void createFactionEvents(const Country& leader, const Country& newAlly);
	void createAnnexEvent(const Country& annexer, const Country& annexed);
	void createSudetenEvent(const Country& annexer, const Country& annexed, const std::vector<int>& claimedStates);
	void createTradeEvent(const Country& leader, const Country& greatPower);
	void createPoliticalEvents(const std::set<std::string>& majorIdeologies);
	void createWarJustificationEvents(const std::set<std::string>& majorIdeologies);
	void importElectionEvents(const std::set<std::string>& majorIdeologies, OnActions& onActions);
	void addPartyChoiceEvent(const std::string& countryTag,
		 const std::set<Vic2::Party>& parties,
		 OnActions& onActions,
		 const std::set<std::string>& majorIdeologies);
	void createStabilityEvents(const std::set<std::string>& majorIdeologies);
	void generateGenericEvents(const Configuration& theConfiguration, const std::set<std::string>& majorIdeologies);

	void giveGovernmentInExileEvent(Event&& gieEvent) { governmentInExileEvent = gieEvent; }

	[[nodiscard]] virtual std::optional<int> getEventNumber(const std::string& eventName) const;

	[[nodiscard]] int getCurrentNationFocusEventNum() const { return nationalFocusEventNumber; }
	[[nodiscard]] const auto& getNationalFocusEvents() const { return nationalFocusEvents; }
	[[nodiscard]] const auto& getNewsEvents() const { return newsEvents; }
	[[nodiscard]] const auto& getPoliticalEvents() const { return politicalEvents; }
	[[nodiscard]] const auto& getWarJustificationEvents() const { return warJustificationEvents; }
	[[nodiscard]] const auto& getElectionsEvents() const { return electionEvents; }
	[[nodiscard]] const auto& getStabilityEvents() const { return stabilityEvents; }
	[[nodiscard]] const auto& getStrikesEvents() const { return strikesEvents; }
	[[nodiscard]] const auto& getMutinyEvents() const { return mutinyEvents; }
	[[nodiscard]] const auto& getGenericEvents() const { return genericEvents; }
	[[nodiscard]] const auto& getGovernmentInExileEvent() const { return governmentInExileEvent; }

  private:
	void addOnTheRise(const std::set<std::string>& majorIdeologies);
	void addMinisterRevolutionEvents(const std::set<std::string>& majorIdeologies);
	void addDemocraticMinisterRevolutionEvents();
	void addFiftyPercentEvents(const std::set<std::string>& majorIdeologies);
	void addRevolutionEvents(const std::set<std::string>& majorIdeologies);
	void addSuppressedEvents(const std::set<std::string>& majorIdeologies);

	static std::string getIdeologicalPicture(const std::string& ideology);

	std::vector<Event> newsEvents;
	int newsEventNumber = 237;
	std::vector<Event> nationalFocusEvents;
	int nationalFocusEventNumber = 0;
	std::vector<Event> politicalEvents;
	int politicalEventNumber = 1;
	std::vector<Event> warJustificationEvents;
	std::vector<Event> electionEvents;
	int electionEventNumber = 4;
	std::map<std::string, Event> stabilityEvents;
	std::map<std::string, Event> strikesEvents;
	std::map<std::string, Event> mutinyEvents;
	std::vector<Event> genericEvents;
	Event governmentInExileEvent;

	std::map<std::string, int> eventNumbers;
};

} // namespace HoI4



#endif // HOI4_EVENTS_H