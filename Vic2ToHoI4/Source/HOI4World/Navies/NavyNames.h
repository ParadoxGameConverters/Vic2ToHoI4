#ifndef NAVY_NAMES_H
#define NAVY_NAMES_H



#include "MtgShipTypeNames.h"
#include "ShipTypeNames.h"
#include <set>



namespace HoI4
{

class NavyNames
{
	public:
		[[nodiscard]] std::set<ShipTypeNames> getShipTypeNames() const { return shipTypeNames; }
		[[nodiscard]] std::set<MtgShipTypeNames> getMtgShipTypeNames() const { return mtgShipTypeNames; }

		void addMtgShipTypeNames(const MtgShipTypeNames& newShipTypeNames) { mtgShipTypeNames.insert(newShipTypeNames); }
		void addShipTypeNames(const ShipTypeNames& newShipTypeNames) { shipTypeNames.insert(newShipTypeNames); }
	
	private:
		std::set<MtgShipTypeNames> mtgShipTypeNames;
		std::set<ShipTypeNames> shipTypeNames;
};

}



#endif // NAVY_NAMES_H
