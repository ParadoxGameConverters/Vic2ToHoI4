#include "src/OutHoi4/Factions/OutFactionTemplates.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Factions/OutFactionTemplate.h"
#include <fstream>



void HoI4::outputFactionTemplates(const std::filesystem::path& outputName,
	 const std::vector<FactionTemplate>& factionTemplates)
{
	const std::filesystem::path folder = outputName / "common/factions/templates";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "ideological_faction_templates.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& factionTemplate: factionTemplates)
	{
		out << factionTemplate << "\n";
	}
}