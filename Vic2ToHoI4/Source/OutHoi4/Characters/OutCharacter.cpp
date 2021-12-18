#include "OutCharacter.h"
#include "OutHoi4/Characters/OutPortrait.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Character& character)
{
	out << "\t" << character.getId() << "={\n";
	out << "\t\tname=" << character.getId() << "\n";
	if (!character.getPortraits().empty())
	{
		out << "\t\tportraits={\n";
		for (const auto& portrait: character.getPortraits())
		{
			out << portrait;
		}
		out << "\t\t}\n";
	}

	if (character.isLeader())
	{
		out << "\t\tcountry_leader={\n";
		out << "\t\t\tideology=" << character.getLeaderIdeology() << "\n";
		if (!character.getLeaderTraits().empty())
		{
			out << "\t\t\ttraits={ ";
			for (const auto& trait: character.getLeaderTraits())
			{
				out << trait << " ";
			}
			out << "}\n";
		}
		out << "\t\t\texpire=\"1965.1.1.1\"\n";
		out << "\t\t\tid=-1\n";
		out << "\t\t}\n";
	}

	if (character.isCommander())
	{
		out << "\t\tcorps_commander={\n";
		if (!character.getCommanderTraits().empty())
		{
			out << "\t\t\ttraits={ ";
			for (const auto& trait: character.getCommanderTraits())
			{
				out << trait << " ";
			}
			out << "}\n";
		}
		out << "\t\t\tskill=" << character.getCommanderSkill() << "\n";
		out << "\t\t\tattack_skill = " << character.getCommanderAttackSkill() << "\n";
		out << "\t\t\tdefense_skill = " << character.getCommanderDefenseSkill() << "\n";
		out << "\t\t\tplanning_skill = " << character.getCommanderPlanningSkill() << "\n";
		out << "\t\t\tlogistics_skill = " << character.getCommanderLogisticsSkill() << "\n";
		out << "\t\t\tlegacy_id = 0\n";
		out << "\t\t}\n";
	}

	if (character.isAdmiral())
	{
		out << "\t\tnavy_leader={\n";
		if (!character.getCommanderTraits().empty())
		{
			out << "\t\t\ttraits={ ";
			for (const auto& trait: character.getAdmiralTraits())
			{
				out << trait << " ";
			}
			out << "}\n";
		}
		out << "\t\t\tskill=" << character.getAdmiralSkill() << "\n";
		out << "\t\t\tattack_skill = " << character.getAdmiralAttackSkill() << "\n";
		out << "\t\t\tdefense_skill = " << character.getAdmiralDefenseSkill() << "\n";
		out << "\t\t\tmaneuvering_skill = " << character.getAdmiralManeuveringSkill() << "\n";
		out << "\t\t\tcoordination_skill = " << character.getAdmiralCoordinationSkill() << "\n";
		out << "\t\t\tlegacy_id = 0\n";
		out << "\t\t}\n";
	}

	out << "\t}\n";

	return out;
}