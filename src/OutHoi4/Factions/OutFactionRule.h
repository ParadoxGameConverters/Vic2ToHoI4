#ifndef OUTHOI4_FACTION_RULE_H
#define OUTHOI4_FACTION_RULE_H



#include "src/HOI4World/Factions/FactionRule.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const FactionRule& theRule);

} // namespace HoI4



#endif // OUTHOI4_FACTION_RULE_H