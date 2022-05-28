#ifndef TANK_MODULES_H
#define TANK_MODULES_H



#include "Parser.h"



namespace HoI4
{


class TankModules: commonItems::parser
{
  public:
	TankModules(std::istream& theStream);

	friend std::ostream& operator<<(std::ostream& output, const TankModules& theModules);

  private:
	std::map<std::string, std::string> modules;
};
} // namespace HoI4
#endif // TANK_MODULES_H