#include "src/OutHoi4/Factions/OutFactionRuleGroups.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>



void HoI4::outputFactionRuleGroups(const std::filesystem::path& outputName,
	 const std::map<std::string, std::vector<std::string>>& ruleGroups)
{
	const std::filesystem::path folder = outputName / "common/factions/rules/groups";
	if (!commonItems::DoesFolderExist(folder) && !std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "rule_groups.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& [ruleGroupId, rules]: ruleGroups)
	{
		out << ruleGroupId << " = {\n";
		out << "\trules = {\n";
		for (const auto& rule: rules)
		{
			out << "\t\t" << rule << "\n";
		}
		out << "\t}\n";
		out << "}\n";
		out << "\n";
	}
}