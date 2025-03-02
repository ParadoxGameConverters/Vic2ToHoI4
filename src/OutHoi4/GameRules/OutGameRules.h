#ifndef OUT_GAME_RULES_H
#define OUT_GAME_RULES_H



#include "src/HOI4World/GameRules/GameRules.h"



namespace HoI4
{

void outputGameRules(const GameRules& rules, const std::filesystem::path& outputName);

}



#endif // OUT_GAME_RULES_H