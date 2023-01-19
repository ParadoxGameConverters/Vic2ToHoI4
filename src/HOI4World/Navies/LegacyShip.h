#ifndef LEGACY_SHIP_H
#define LEGACY_SHIP_H


#include "src/HOI4World/Navies/Ship.h"
#include <ostream>
#include <string>



namespace HoI4
{

class LegacyShip final: public Ship
{
  public:
	LegacyShip(const std::string& name, const std::string& type, const std::string& equipment, const std::string& owner):
		 Ship(name, type, equipment, owner)
	{
	}

	friend std::ostream& operator<<(std::ostream& output, const LegacyShip& instance);
};

} // namespace HoI4



#endif // LEGACY_SHIP_H