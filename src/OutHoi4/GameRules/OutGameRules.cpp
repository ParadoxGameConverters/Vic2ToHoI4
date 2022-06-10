#include "src/OutHoi4/GameRules/OutGameRules.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include <fstream>



void HoI4::outputGameRules(const GameRules& rules, const std::string& outputName)
{
	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/game_rules"))
	{
		throw std::runtime_error{"Could not create output/" + outputName + "/common/game_rules"};
	}
	std::ofstream rulesFile("output/" + outputName + "/common/game_rules/00_game_rules.txt");
	if (!rulesFile.is_open())
	{
		throw std::runtime_error{"Could not open output/" + outputName + "/common/game_rules/00_game_rules.txt"};
	}

	for (const auto& rule: rules.getGameRules())
	{
		rulesFile << rule;
	}

	rulesFile.close();
}