#include "src/OutHoi4/Characters/OutAdmiralData.h"



std::ostream& HoI4::operator<<(std::ostream& out, const AdmiralData& admiral_data)
{
	out << "\t\tnavy_leader={\n";
	if (!admiral_data.getTraits().empty())
	{
		out << "\t\t\ttraits={ ";
		for (const auto& trait: admiral_data.getTraits())
		{
			out << trait << " ";
		}
		out << "}\n";
	}
	out << "\t\t\tskill=" << admiral_data.getSkill() << "\n";
	out << "\t\t\tattack_skill=" << admiral_data.getAttackSkill() << "\n";
	out << "\t\t\tdefense_skill=" << admiral_data.getDefenseSkill() << "\n";
	out << "\t\t\tmaneuvering_skill=" << admiral_data.getManeuveringSkill() << "\n";
	out << "\t\t\tcoordination_skill=" << admiral_data.getCoordinationSkill() << "\n";
	out << "\t\t\tlegacy_id=0\n";
	out << "\t\t}\n";

	return out;
}