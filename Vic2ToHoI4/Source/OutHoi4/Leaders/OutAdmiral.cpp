#include "OutAdmiral.h"
#include <ostream>



std::ostream& HoI4::operator<<(std::ostream& output, const Admiral& admiral)
{
	output << "create_navy_leader = {\n";
	output << "\tname = \"" << admiral.name << "\"\n";
	output << "\ttraits = { ";
	for (const auto& trait: admiral.traits)
	{
		output << trait << " ";
	}
	output << "}\n";
	output << "\tskill = " << admiral.skill << "\n";
	output << "\tattack_skill = " << admiral.attackSkill << "\n";
	output << "\tdefense_skill = " << admiral.defenseSkill << "\n";
	output << "\tmaneuvering_skill = " << admiral.maneuveringSkill << "\n";
	output << "\tcoordination_skill = " << admiral.coordinationSkill << "\n";
	output << "}\n";

	return output;
}