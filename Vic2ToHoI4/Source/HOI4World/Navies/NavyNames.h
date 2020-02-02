#ifndef NAVY_NAMES_H
#define NAVY_NAMES_H



#include "ShipTypeNames.h"
#include <set>



namespace HoI4
{

class NavyNames
{
	public:
		[[nodiscard]] std::set<ShipTypeNames> getShipTypeNames() const { return shipTypeNames; }

		void addShipTypeNames(const ShipTypeNames& newShipTypeNames) { shipTypeNames.insert(newShipTypeNames); }
	
	private:
		std::set<ShipTypeNames> shipTypeNames;
};

}



#endif // NAVY_NAMES_H
