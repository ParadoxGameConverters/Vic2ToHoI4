#include "src/OutHoi4/Factions/OutFactionGoals.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Factions/OutFactionGoal.h"
#include <fstream>



void HoI4::outputFactionGoals(const std::filesystem::path& outputName,
	 const std::vector<std::shared_ptr<FactionGoal>>& factionGoals)
{
	const std::filesystem::path folder = outputName / "common/factions/goals";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "ideological_faction_goals.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& factionGoal: factionGoals)
	{
		out << *factionGoal << "\n";
	}
}