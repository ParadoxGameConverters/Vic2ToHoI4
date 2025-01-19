#ifndef OUT_ADJACENCY_RULE_H
#define OUT_ADJACENCY_RULE_H



#include "src/HOI4World/Map/AdjacencyRule.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const AdjacencyRule& outAdjacencyRule);

} // namespace HoI4



#endif // OUT_ADJACENCY_RULE_H