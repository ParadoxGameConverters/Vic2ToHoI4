#include "OutGeneral.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& output, const General& general)
{
	output << "create_corps_commander = {\n";
	output << "\tname = \"" << general.name << "\"\n";
	output << "\ttraits = { ";
	for (const auto& trait: general.traits)
	{
		output << trait << " ";
	}
	output << "}\n";
	output << "\tskill = " << general.skill << "\n";
	output << "\tattack_skill = " << general.attackSkill << "\n";
	output << "\tdefense_skill = " << general.defenseSkill << "\n";
	output << "\tplanning_skill = " << general.planningSkill << "\n";
	output << "\tlogistics_skill = " << general.logisticsSkill << "\n";
	output << "}\n";

	return output;
}