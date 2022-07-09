#ifndef SRC_HOI4_WORLD_MAP_PATH_POINT_H
#define SRC_HOI4_WORLD_MAP_PATH_POINT_H



#include "src/HOI4World/Map/PossiblePath.h"
#include <optional>



namespace HoI4
{

struct PathPoint
{
	int province = 0;
	double cost = 0.0;
	std::optional<HoI4::PossiblePath> in_connection;
};


bool operator<(const PathPoint& lhs, const PathPoint& rhs);

} // namespace HoI4



#endif // SRC_HOI4_WORLD_MAP_PATH_POINT_H