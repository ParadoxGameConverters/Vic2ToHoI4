#ifndef SCENARIO_MOD_H
#define SCENARIO_MOD_H

#include "src/HOI4World/Decisions/Decision.h"
#include "src/HOI4World/Decisions/DecisionsCategory.h"
#include "src/HOI4World/Events/Event.h"

class ScenarioMod
{
  public:
	ScenarioMod() = default;

	[[nodiscard]] auto GetDecisions() const { return decisions_; };
	[[nodiscard]] auto GetDecisionCategories() const { return decision_categories_; };
	[[nodiscard]] auto GetEvents() const { return events_; };
	[[nodiscard]] auto GetName() const { return name_; };

	// When I ask myself why I did this later: https://google.github.io/styleguide/cppguide.html#Inheritance
	// (Delete comment once design is settled)
  protected:
	void AddDecision(const HoI4::decision& decision) { decisions_.push_back(decision); };
	void AddDecisionCategory(const HoI4::DecisionsCategory& decision_category)
	{
		decision_categories_.push_back(decision_category);
	};
	void AddEvent(const HoI4::Event& hoi4_event) { events_.push_back(hoi4_event); };
	void SetName(const std::string name) { name_ = name; };

  private:
	std::vector<HoI4::decision> decisions_;
	std::vector<HoI4::DecisionsCategory> decision_categories_;
	std::vector<HoI4::Event> events_;
	std::string name_;
};
#endif // SCENARIO_MOD_H