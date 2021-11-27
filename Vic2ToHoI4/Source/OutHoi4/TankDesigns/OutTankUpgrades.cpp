#include "OutTankUpgrades.h"



std::ostream& HoI4::operator<<(std::ostream& output, const TankUpgrades& theUpgrades)
{
	output << "\t\tupgrades = {\n";
	for (const auto& upgrade: theUpgrades.upgrades)
	{
		output << "\t\t\t" << upgrade.first << " = " << upgrade.second << "\n";
	}
	output << "\t\t}\n";

	return output;
}