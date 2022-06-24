#ifndef SCENARIO_MOD_H
#define SCENARIO_MOD_H

#include "src/HOI4World/Decisions/DecisionsCategories.h"
#include "src/HOI4World/Decisions/DecisionsInCategory.h"
#include "src/HOI4World/Events/Event.h"

class ScenarioMod
{
  public:
	ScenarioMod() = default;

	[[nodiscard]] auto GetDecisionsFromCategory(const std::string category) const { return decisions_.at(category); };
	[[nodiscard]] auto GetAllDecisionsByCategory() const { return decisions_; };
	[[nodiscard]] auto GetDecisionCategories() const { return &decision_categories_; };
	[[nodiscard]] auto GetEvents() const { return events_; };
	[[nodiscard]] auto GetElectionOnActions() const { return events_; };
	[[nodiscard]] auto GetName() const { return name_; };

	virtual void OutputRoleSpecifics(std::string output_name) const {}

	// When I ask myself why I did this later: https://google.github.io/styleguide/cppguide.html#Inheritance
	// (Delete comment once design is settled)
  protected:
	void AddDecisionInCategory(HoI4::decision decision, const std::string category)
	{
		decisions_.at(category).addDecision(decision);
	};
	void AddDecisionsInCategory(HoI4::DecisionsInCategory decisions, const std::string category)
	{
		decisions_.emplace(category, decisions);
	};
	void AddDecisionCategory(const HoI4::DecisionsCategory& decision_category)
	{
		decision_categories_->addCategory(decision_category);
	};
	void AddEvent(const HoI4::Event& hoi4_event) { events_.push_back(hoi4_event); }

	void SetDecisionCategories(std::unique_ptr<HoI4::DecisionsCategories>& decision_categories)
	{
		decision_categories_ = std::move(decision_categories);
	}
	void SetDecisions(std::map<std::string, HoI4::DecisionsInCategory> decisions) { decisions_ = decisions; }
	void SetName(const std::string name) { name_ = name; }

  private:
	std::map<std::string, HoI4::DecisionsInCategory> decisions_;
	std::unique_ptr<HoI4::DecisionsCategories> decision_categories_;
	std::vector<HoI4::Event> events_;
	std::string name_;
};
#endif // SCENARIO_MOD_H