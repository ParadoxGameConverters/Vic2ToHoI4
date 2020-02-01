#ifndef OUT_SUPPLY_ZONE_H
#define OUT_SUPPLY_ZONE_H


#include "../../HOI4World/Map/HoI4SupplyZone.h"
#include "../../Configuration.h"



namespace HoI4
{
	
void outputSupplyZone(
	const HoI4SupplyZone& supplyZone,
	const std::string& filename,
	const Configuration& theConfiguration
);

}



#endif // OUT_SUPPLY_ZONE_H