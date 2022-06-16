#include "src/OutHoi4/ScenarioCreator/OutScenario.h"
#include "src/OutHoi4/ScenarioCreator/OutScenarioMod.h"

void HoI4::OutputScenario(const ScenarioCreator& scenario, std::string output_name)
{
	std::ofstream output("output/" + output_name + "/" + scenario.GetSaveName() + "_scenario.txt");

	for (const auto& assignment: scenario.GetAssignments())
	{
		const auto& tag = assignment.first;
		const auto& role_name = assignment.second;

		output << tag + " = " + role_name + "\n";
	}

	for (const auto& mod: scenario.GetScenarioMods())
	{
		OutputScenarioMod(*mod, output_name);
	}
}
