#include "src/OutHoi4/Characters/OutCommanderData.h"



std::ostream& HoI4::operator<<(std::ostream& out, const CommanderData& commanderData)
{
	if (commanderData.getLevel() == CommanderLevel::FieldMarshal)
	{
		out << "\t\tfield_marshal={\n";
	}
	else
	{
		out << "\t\tcorps_commander={\n";
	}
	if (!commanderData.getTraits().empty())
	{
		out << "\t\t\ttraits={ ";
		for (const auto& trait: commanderData.getTraits())
		{
			out << trait << " ";
		}
		out << "}\n";
	}
	out << "\t\t\tskill=" << commanderData.getSkill() << "\n";
	out << "\t\t\tattack_skill=" << commanderData.getAttackSkill() << "\n";
	out << "\t\t\tdefense_skill=" << commanderData.getDefenseSkill() << "\n";
	out << "\t\t\tplanning_skill=" << commanderData.getPlanningSkill() << "\n";
	out << "\t\t\tlogistics_skill=" << commanderData.getLogisticsSkill() << "\n";
	out << "\t\t\tlegacy_id=0\n";
	out << "\t\t}\n";

	return out;
}