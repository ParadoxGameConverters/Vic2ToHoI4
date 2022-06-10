#include "src/OutHoi4/Navies/OutMtgShip.h"
#include <limits>



std::ostream& HoI4::operator<<(std::ostream& output, const MtgShip& instance)
{
	output << "\t\t\tship = { name = \"" << instance.name;
	output << "\" definition = " << instance.type;
	if (instance.experience > std::numeric_limits<float>::epsilon())
	{
		output << " start_experience_factor = " << instance.experience;
	}
	output << " equipment = { " << instance.equipment;
	output << " = { amount = 1 owner = " << instance.owner;
	output << " version_name = \"" << instance.version << "\" } }";

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