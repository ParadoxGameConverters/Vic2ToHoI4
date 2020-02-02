#ifndef NAVY_NAMES_H
#define NAVY_NAMES_H



#include "ShipTypeNames.h"
#include <set>



namespace HoI4
{

class NavyNames
{
	public:
		[[nodiscard]] std::set<ShipTypeNames> getShipTypeNames() const { return std::set<ShipTypeNames>{}; }
};

}



#endif // NAVY_NAMES_H
