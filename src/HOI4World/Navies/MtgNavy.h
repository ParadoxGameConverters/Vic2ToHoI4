#ifndef MTG_NAVY_H
#define MTG_NAVY_H



#include "src/HOI4World/Navies/MtgShip.h"
#include "src/HOI4World/Navies/Navy.h"
#include <vector>



namespace HoI4
{

class MtgNavy final: public Navy
{
  public:
	MtgNavy(const std::string& name, const int location, const int base): Navy(name, location, base) {}

	void addShip(Ship& newShip) override { ships.push_back(dynamic_cast<MtgShip&>(newShip)); }

	[[nodiscard]] size_t getNumShips() const override { return ships.size(); }

	[[nodiscard]] float getStrength() const;

	friend std::ostream& operator<<(std::ostream& output, const MtgNavy& instance);

  private:
	std::vector<MtgShip> ships;
};

} // namespace HoI4



#endif // MTG_NAVY_H