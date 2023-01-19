#ifndef TANK_UPGRADES_H
#define TANK_UPGRADES_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>



namespace HoI4
{

class TankUpgrades: commonItems::parser
{
  public:
	TankUpgrades(std::istream& theStream);
	auto&& takeUpgrades() { return std::move(upgrades); }

	friend std::ostream& operator<<(std::ostream& output, const TankUpgrades& theUpgrades);

  private:
	std::map<std::string, int> upgrades;
};

} // namespace HoI4



#endif // TANK_UPGRADES_H