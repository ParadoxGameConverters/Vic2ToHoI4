#include "src/OutHoi4/ScenarioCreator/OutScenarioMod.h"
#include "src/OutHoi4/Decisions/OutDecisionsCategories.h"
#include <fstream>

void HoI4::OutputScenarioMod(const ScenarioMod& mod, std::string output_name)
{
	outputDecisionCategories("output/" + output_name + "/common/decisions/categories/scenario_decision_categories.txt",
		 *mod.GetDecisionCategories()->get());

	std::ofstream decision_output("output/" + output_name + "/common/decisions/scenario_decisions.txt");
	for (const auto& decCat: mod.GetAllDecisionsByCategory())
		decision_output << decCat.second;

	std::ofstream debugTest("output/" + output_name + "/name.txt");
	debugTest << mod.GetName();
}