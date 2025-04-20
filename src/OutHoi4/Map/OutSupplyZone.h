#ifndef OUT_SUPPLY_ZONE_H
#define OUT_SUPPLY_ZONE_H



#include "src/Configuration.h"
#include "src/HOI4World/Map/SupplyZone.h"



namespace HoI4
{

void outputSupplyZone(const SupplyZone& supplyZone,
	 const std::filesystem::path& filename,
	 const std::filesystem::path& outputName);

}



#endif // OUT_SUPPLY_ZONE_H