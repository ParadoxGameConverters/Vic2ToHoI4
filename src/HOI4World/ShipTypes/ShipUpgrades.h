#ifndef SHIP_UPGRADES_H
#define SHIP_UPGRADES_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>



namespace HoI4
{

class ShipUpgrades: commonItems::parser
{
  public:
	ShipUpgrades(std::istream& theStream);
	auto&& takeUpgrades() { return std::move(upgrades); }

  private:
	std::map<std::string, int> upgrades;
};

} // namespace HoI4



#endif // SHIP_UPGRADES_H