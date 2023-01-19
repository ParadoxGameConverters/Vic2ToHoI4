#ifndef NAVY_H
#define NAVY_H



#include "src/HOI4World/Navies/LegacyShip.h"
#include <string>



namespace HoI4
{


class Navy
{
  public:
	Navy(std::string name, const int location, const int base): name(std::move(name)), location(location), base(base) {}

	Navy() = default;
	virtual ~Navy() = default;
	Navy(const Navy&) = default;
	Navy(Navy&&) = default;
	Navy& operator=(const Navy&) = default;
	Navy& operator=(Navy&&) = default;

	virtual void addShip(Ship& newShip) = 0;

	[[nodiscard]] virtual size_t getNumShips() const = 0;

  protected:
	std::string name;
	int location = 0;
	int base = 0;
};


} // namespace HoI4



#endif // HOI4_NAVY_H
