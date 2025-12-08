#include "src/OutHoi4/Factions/OutFactionRules.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Factions/OutFactionRule.h"
#include <fstream>



void HoI4::outputFactionRules(const std::filesystem::path& outputName, const std::vector<FactionRule>& factionRules)
{
	const std::filesystem::path folder = outputName / "common/factions/rules";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "ideological_faction_rules.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& factionRule: factionRules)
	{
		out << factionRule << "\n";
	}
}