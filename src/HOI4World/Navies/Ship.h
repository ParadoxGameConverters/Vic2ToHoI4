#ifndef SHIP_H
#define SHIP_H


#include <string>



namespace HoI4
{

class Ship
{
  public:
	Ship(std::string name, std::string type, std::string equipment, std::string owner):
		 name(std::move(name)), type(std::move(type)), equipment(std::move(equipment)), owner(std::move(owner))
	{
	}

	Ship() = default;
	virtual ~Ship() = default;
	Ship(const Ship&) = default;
	Ship(Ship&&) = default;
	Ship& operator=(const Ship&) = default;
	Ship& operator=(Ship&&) = default;

  protected:
	std::string name;
	std::string type;
	std::string equipment;
	std::string owner;
};

} // namespace HoI4



#endif // SHIP_H