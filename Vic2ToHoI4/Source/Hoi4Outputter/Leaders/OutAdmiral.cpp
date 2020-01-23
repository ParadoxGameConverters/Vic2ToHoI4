#include "../../HOI4World/Leaders/Admiral.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& output, const Admiral& instance)
{
	output << "create_navy_leader = {\n";
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
	output << "\tmaneuvering_skill = " << instance.maneuveringSkill << "\n";
	output << "\tcoordination_skill = " << instance.coordinationSkill << "\n";
	output << "}\n";

	return output;
}