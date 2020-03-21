#include "OutGameRules.h"
#include <fstream>



void HoI4::outputGameRules(const GameRules& rules, const Configuration& theConfiguration)
{
	std::ofstream rulesFile("output/" + theConfiguration.getOutputName() + "/common/game_rules/00_game_rules.txt");

	for (const auto& rule: rules.getGameRules())
	{
		rulesFile << rule;
	}

	rulesFile.close();
}