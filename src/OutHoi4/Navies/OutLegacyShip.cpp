#include "src/OutHoi4/Navies/OutLegacyShip.h"



std::ostream& HoI4::operator<<(std::ostream& output, const LegacyShip& instance)
{
	output << "\t\t\tship = { name = \"" << instance.name;
	output << "\" definition = " << instance.type;
	output << " equipment = { " << instance.equipment;
	output << " = { amount = 1 owner = " << instance.owner;
	output << " } }";

	if (instance.type == "carrier")
	{
		output << "\n";
		output << "\t\t\t\tair_wings = {\n";

		output << "\t\t\t\t\tcv_fighter_equipment_0 =  { owner = \"";
		output << instance.owner << "\" amount = 8 } # historical: 36\n";

		output << "\t\t\t\t\tcv_CAS_equipment_1 =  { owner = \"";
		output << instance.owner << "\" amount = 14 } # historical: 15\n";

		output << "\t\t\t\t\tcv_nav_bomber_equipment_1 =  { owner = \"";
		output << instance.owner << "\" amount = 8 } # historical: 12\n";

		output << "\t\t\t\t}\n";
		output << "\t\t\t}\n";
	}
	else
	{
		output << " }\n";
	}

	return output;
}