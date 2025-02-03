#ifndef OUTHOI4_MAP_OUTRAILWAYS_H
#define OUTHOI4_MAP_OUTRAILWAYS_H



#include "src/HOI4World/Map/Railway.h"
#include <vector>



namespace HoI4
{

void outputRailways(const std::filesystem::path& path, const std::vector<Railway>& railways);

}



#endif // OUTHOI4_MAP_OUTRAILWAYS_H