#ifndef OUTHOI4_FACTION_GOAL_H
#define OUTHOI4_FACTION_GOAL_H



#include "src/HOI4World/Factions/FactionGoal.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const FactionGoal& theGoal);

} // namespace HoI4



#endif // OUTHOI4_FACTION_GOAL_H