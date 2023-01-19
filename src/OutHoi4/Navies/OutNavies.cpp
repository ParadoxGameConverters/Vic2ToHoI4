#include "src/OutHoi4/Navies/OutNavies.h"



void HoI4::outputLegacyNavies(const Navies& navies,
	 const technologies& technologies,
	 const std::string_view tag,
	 std::ostream& output)
{
	output << "units = {\n";
	for (const auto& navy: navies.getLegacyNavies())
	{
		output << navy;
	}
	output << "}\n";
	output << "\n";
	output << "instant_effect = {\n";
	if (technologies.hasTechnology("basic_destroyer"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = destroyer_2\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 3\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 10\n";
		output << "\t}\n";
	}
	else if (technologies.hasTechnology("early_destroyer"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = destroyer_1\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 3\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 10\n";
		output << "\t}\n";
	}
	if (technologies.hasTechnology("basic_battleship"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = battleship_2\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 8\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 3\n";
		output << "\t}\n";
	}
	else if (technologies.hasTechnology("early_battleship"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = battleship_1\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 8\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 3\n";
		output << "\t}\n";
	}
	output << "}";
}


void HoI4::outputMtgNavies(const Navies& navies,
	 const technologies& technologies,
	 const std::string_view tag,
	 std::ostream& output)
{
	output << "units = {\n";
	for (const auto& navy: navies.getMtgNavies())
	{
		output << navy;
	}
	output << "}\n";
	output << "\n";
	output << "instant_effect = {\n";
	if (technologies.hasTechnology("basic_ship_hull_light"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = ship_hull_light_2\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t\tversion_name = \"1936 Destroyer\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 3\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 10\n";
		output << "\t}\n";
	}
	else if (technologies.hasTechnology("early_ship_hull_light"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = ship_hull_light_1\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t\tversion_name = \"Early Destroyer\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 3\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 10\n";
		output << "\t}\n";
	}
	if (technologies.hasTechnology("basic_ship_hull_heavy"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = ship_hull_heavy_2\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t\tversion_name = \"1936 Battleship\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 8\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 3\n";
		output << "\t}\n";
	}
	else if (technologies.hasTechnology("early_ship_hull_heavy"))
	{
		output << "\tadd_equipment_production = {\n";
		output << "\t\tequipment = {\n";
		output << "\t\t\ttype = ship_hull_heavy_1\n";
		output << "\t\t\tcreator = \"" << tag << "\"\n";
		output << "\t\t\tversion_name = \"Early Battleship\"\n";
		output << "\t\t}\n";
		output << "\t\trequested_factories = 8\n";
		output << "\t\tprogress = 0.25\n";
		output << "\t\tamount = 3\n";
		output << "\t}\n";
	}
	output << "}";
}