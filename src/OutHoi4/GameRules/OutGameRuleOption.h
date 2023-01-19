#ifndef OUT_GAME_RULE_OPTION
#define OUT_GAME_RULE_OPTION


#include "src/HOI4World/GameRules/GameRuleOption.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const GameRuleOption& option);

}



#endif // OUT_GAME_RULE_OPTION