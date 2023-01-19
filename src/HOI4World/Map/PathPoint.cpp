#include "src/HOI4World/Map/PathPoint.h"



// higher is prioritized where we want lower to be in priority queues, so reverse the meaning of <
bool HoI4::operator<(const HoI4::PathPoint& lhs, const HoI4::PathPoint& rhs)
{
	return lhs.cost > rhs.cost;
}