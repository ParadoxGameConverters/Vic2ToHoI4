#include "src/OutHoi4/ScenarioBuilder/OutScenario.h"

void HoI4::outputScenario(const ScenarioBuilder& scenario, std::string& outputName, std::string& saveName)
{
	std::ofstream output("output/" + outputName + "/" + saveName + "_scenario.txt");

	for (const auto& assignment: scenario.getAssignments())
	{
		const auto& tag = assignment.first;
		const auto& roleName = assignment.second;

		output << tag + " = " + roleName + "\n";
	}

	// Output all role mods? Or will it all be part of Country class?
}
