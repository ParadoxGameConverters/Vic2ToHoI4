#include "src/OutHoi4/ScenarioCreator/OutScenarioMod.h"
#include <fstream>

void HoI4::OutputScenarioMod(const ScenarioMod& mod, std::string output_name)
{
	std::ofstream decision_output("output/" + output_name + "/common/decisions/scenario_decisions.txt");
	//for (const auto& dec: mod.GetDecisions())
	//	decision_output << dec;

	std::ofstream debugTest("output/" + output_name + "/name.txt");
	debugTest << mod.GetName();
}