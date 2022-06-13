#ifndef SCENARIO_MOD_H
#define SCENARIO_MOD_H

#include "src/HOI4World/Decisions/Decision.h"
#include <src/HOI4World/Decisions/DecisionsCategory.h>
#include <src/HOI4World/Events/Event.h>

class ScenarioMod
{
  public:
	ScenarioMod() = default;

	[[nodiscard]] auto getDecisions() const { return decisions; };
	[[nodiscard]] auto getDecisionCategories() const { return decisionCategories; };
	[[nodiscard]] auto getEvents() const { return events; };

  protected:
	std::vector<HoI4::decision> decisions;
	std::vector<HoI4::DecisionsCategory> decisionCategories;
	std::vector<HoI4::Event> events;
};
#endif // SCENARIO_MOD_H