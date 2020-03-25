#include "../../HOI4World/Leaders/General.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& output, const General& instance)
{
	output << "create_corps_commander = {\n";
	output << "\tname = \"" << instance.name << "\"\n";
	output << "\tpicture = \"" << instance.picture << "\"\n";
	output << "\ttraits = { ";
	for (const auto& trait : instance.traits)
	{
		output << trait << " ";
	}
	output << "}\n";
	output << "\tskill = " << instance.skill << "\n";
	output << "\tattack_skill = " << instance.attackSkill << "\n";
	output << "\tdefense_skill = " << instance.defenseSkill << "\n";
	output << "\tplanning_skill = " << instance.planningSkill << "\n";
	output << "\tlogistics_skill = " << instance.logisticsSkill << "\n";
	output << "}\n";

	return output;
}