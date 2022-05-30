#ifndef LEGACY_NAVY_H
#define LEGACY_NAVY_H



#include "LegacyShip.h"
#include "Navy.h"
#include <vector>



namespace HoI4
{

class LegacyNavy final: public Navy
{
  public:
	LegacyNavy(const std::string& name, const int location, const int base): Navy(name, location, base) {}

	void addShip(Ship& newShip) override { ships.push_back(dynamic_cast<LegacyShip&>(newShip)); }

	[[nodiscard]] size_t getNumShips() const override { return ships.size(); }

	friend std::ostream& operator<<(std::ostream& output, const LegacyNavy& instance);

  private:
	std::vector<LegacyShip> ships;
};

} // namespace HoI4



#endif // LEGACY_NAVY_H