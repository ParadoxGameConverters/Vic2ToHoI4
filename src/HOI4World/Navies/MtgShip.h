#ifndef MTG_SHIP_H
#define MTG_SHIP_H


#include "Ship.h"
#include <ostream>
#include <string>



namespace HoI4
{

class MtgShip final: public Ship
{
  public:
	MtgShip(const std::string& name,
		 const std::string& type,
		 const std::string& equipment,
		 const std::string& owner,
		 std::string version,
		 const float& experience):
		 Ship(name, type, equipment, owner),
		 version(std::move(version)), experience(experience)
	{
	}

	[[nodiscard]] float getStrength() const;

	friend std::ostream& operator<<(std::ostream& output, const MtgShip& instance);

  private:
	std::string version;
	float experience = 0.0;
};

} // namespace HoI4



#endif // MTG_SHIP_H