#include "src/OutHoi4/ShipTypes/OutLegacyShipVariant.h"



std::ostream& HoI4::operator<<(std::ostream& output, const LegacyShipVariant& theVariant)
{
	output << "\tcreate_equipment_variant = {\n";
	output << "\t\tname = \"" + theVariant.name + "\"\n";
	output << "\t\ttype = " + theVariant.type + "\n";
	output << "\t\tupgrades = {\n";
	for (const auto& upgrade: theVariant.upgrades)
	{
		output << "\t\t\t" + upgrade.first + " = " + std::to_string(upgrade.second) + "\n";
	}
	output << "\t\t}\n";
	if (theVariant.obsolete)
	{
		output << "\t\tobsolete = yes\n";
	}
	output << "\t}\n";
	output << "\n";

	return output;
}