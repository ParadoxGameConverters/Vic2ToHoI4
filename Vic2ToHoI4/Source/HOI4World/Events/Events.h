#ifndef HOI4_EVENTS_H
#define HOI4_EVENTS_H



#include "Event.h"
#include "../../V2World/Party.h"
#include "newParser.h"
#include <functional>
#include <map>
#include <memory>
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

		void createFactionEvents(std::shared_ptr<HoI4::Country> Leader, std::shared_ptr<HoI4::Country> newAlly);
		void createAnnexEvent(std::shared_ptr<HoI4::Country> Annexer, std::shared_ptr<HoI4::Country> Annexed);
		void createSudetenEvent(std::shared_ptr<HoI4::Country> Annexer, std::shared_ptr<HoI4::Country> Annexed, const std::vector<int>& claimedStates);
		void createTradeEvent(std::shared_ptr<HoI4::Country> leader, std::shared_ptr<HoI4::Country> GC);
		void createPoliticalEvents(const std::set<std::string>& majorIdeologies);
		void createWarJustificationEvents(const std::set<std::string>& majorIdeologies);
		void importElectionEvents(const std::set<std::string>& majorIdeologies, HoI4::OnActions& onActions);
		void addPartyChoiceEvent(const std::string& countryTag, const std::set<Vic2::Party, std::function<bool (const Vic2::Party&, const Vic2::Party&)>>& parties, HoI4::OnActions& onActions, const std::set<std::string>& majorIdeologies);
		void createStabilityEvents(const std::set<std::string>& majorIdeologies);

		virtual std::optional<int> getEventNumber(const std::string& eventName) const;

		int getCurrentNationFocusEventNum() const { return nationalFocusEventNumber; }
		const auto& getNationalFocusEvents() const { return nationalFocusEvents; }
		const auto& getNewsEvents() const { return newsEvents; }
		const auto& getPoliticalEvents() const { return politicalEvents; }
		const auto& getWarJustificationEvents() const { return warJustificationEvents; }
		const auto& getElectionsEvents() const { return electionEvents; }
		const auto& getStabilityEvents() const { return stabilityEvents; }
		const auto& getStrikesEvents() const { return strikesEvents; }
		const auto& getMutinyEvents() const { return mutinyEvents; }


	private:
		Events(const Events&) = delete;
		Events& operator=(const Events&) = delete;

		void addMinisterRevolutionEvents(const std::set<std::string>& majorIdeologies);
		void addDemocraticMinisterRevolutionEvents(const std::set<std::string>& majorIdeologies);
		void addFiftyPercentEvents(const std::set<std::string>& majorIdeologies);
		void addRevolutionEvents(const std::set<std::string>& majorIdeologies);
		void addSuppressedEvents(const std::set<std::string>& majorIdeologies);
		std::string getIdeologicalPicture(const std::string& ideology) const;

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

		std::map<std::string, int> eventNumbers;
};

}



#endif // HOI4_EVENTS_H