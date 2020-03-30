#ifndef OUT_SUPPLY_ZONE_H
#define OUT_SUPPLY_ZONE_H



#include "../../Configuration.h"
#include "../../HOI4World/Map/SupplyZone.h"



namespace HoI4
{

void outputSupplyZone(const SupplyZone& supplyZone, const std::string& filename, const std::string& outputName);

}



#endif // OUT_SUPPLY_ZONE_H