#ifndef OUT_GAME_RULE_H
#define OUT_GAME_RULE_H



#include "src/HOI4World/GameRules/GameRule.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const GameRule& rule);

}



#endif // OUT_GAME_RULE_H