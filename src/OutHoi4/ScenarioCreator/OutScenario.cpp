#include "src/OutHoi4/ScenarioCreator/OutScenario.h"
#include "src/OutHoi4/ScenarioCreator/OutScenarioMod.h"

void HoI4::outputScenario(const ScenarioCreator& scenario, std::string outputName)
{
	std::ofstream output("output/" + outputName + "/" + scenario.getSaveName() + "_scenario.txt");

	for (const auto& assignment: scenario.getAssignments())
	{
		const auto& tag = assignment.first;
		const auto& roleName = assignment.second;

		output << tag + " = " + roleName + "\n";
	}

	for (const auto& mod: scenario.getScenarioMods())
	{
		outputScenarioMod(*mod, outputName);
	}
}
