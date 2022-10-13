#include "src/OutHoi4/Countries/OutEquipment.h"



std::ostream& HoI4::operator<<(std::ostream& output, const HoI4::Equipment& equipment)
{
	if (equipment.GetAmount() > 0)
	{
		std::string indents;
		if (equipment.GetLimit().has_value())
		{
			indents = "\t";
			output << "if = {\n";
			output << "\tlimit = { " << *equipment.GetLimit() << " }\n";
		}
		output << indents << "add_equipment_to_stockpile = ";
		output << "{ type = " << equipment.GetType();
		if (equipment.GetVariant().has_value())
		{
			output << " variant_name = \"" << *equipment.GetVariant() << "\"";
		}
		output << " amount = " << equipment.GetAmount() << " producer = " << equipment.GetOwner() << " }\n";

		if (equipment.GetLimit().has_value())
		{
			output << "}\n";
		}
	}

	return output;
}