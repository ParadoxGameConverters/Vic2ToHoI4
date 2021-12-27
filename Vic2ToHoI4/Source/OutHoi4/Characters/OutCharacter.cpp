#include "OutCharacter.h"
#include "OutHoi4/Characters/OutCommanderData.h"
#include "OutHoi4/Characters/OutCountryLeaderData.h"
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

	if (const auto& countryLeaderData = character.getCountryLeaderData(); countryLeaderData.has_value())
	{
		out << *countryLeaderData;
	}

	if (const auto& commanderData = character.getCommanderData(); commanderData.has_value())
	{
		out << *commanderData;
	}

	if (character.isAdmiral())
	{
		out << "\t\tnavy_leader={\n";
		if (!character.getAdmiralTraits().empty())
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