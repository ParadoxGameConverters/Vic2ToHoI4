#ifndef GAME_RULES_H
#define GAME_RULES_H



#include "src/HOI4World/GameRules/GameRule.h"
#include "external/common_items/ConvenientParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class GameRules
{
  public:
	class Parser;
	explicit GameRules(std::vector<GameRule> _gameRules): gameRules(std::move(_gameRules)) {}

	[[nodiscard]] const auto& getGameRules() const { return gameRules; }

	void updateRules();

  private:
	std::vector<GameRule> gameRules;
};


class GameRules::Parser: commonItems::parser
{
  public:
	GameRules parseRulesFile(const std::string& filename);
};

} // namespace HoI4



#endif // GAME_RULES_H