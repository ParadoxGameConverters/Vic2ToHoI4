#include "OutScenarioMod.h"
#include <fstream>

void HoI4::outputScenarioMod(const ScenarioMod& mod, std::string& outputName)
{
	std::ofstream decisionOutput("output/" + outputName + "/common/decisions/scenario_decisions.txt");
	for (const auto& dec: mod.getDecisions())
		decisionOutput << dec;

	// std::ofstream decisionCategoryOutput("output/" + outputName +
	// "/common/decision_categories/scenario_decision_categorgies.txt"); for (const auto& decCategory:
	// mod.getDecisionCategories()) 	decisionOutput << decCategory;

	// std::ofstream decisionOutput("output/" + outputName + "/common/decisions/scenario_decisions.txt");
	// for (const auto& dec: mod.getDecisions())
	//	decisionOutput << dec;

	// std::ofstream decisionOutput("output/" + outputName + "/common/decisions/scenario_decisions.txt");
	// for (const auto& dec: mod.getDecisions())
	//	decisionOutput << dec;
}
