#include "OutCharacter.h"
#include "src/OutHoi4/Characters/OutAdmiralData.h"
#include "src/OutHoi4/Characters/OutAdvisorData.h"
#include "src/OutHoi4/Characters/OutCommanderData.h"
#include "src/OutHoi4/Characters/OutCountryLeaderData.h"
#include "src/OutHoi4/Characters/OutPortrait.h"



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

	if (const auto& advisorData = character.getAdvisorData(); advisorData.has_value())
	{
		out << *advisorData;
	}

	if (const auto& countryLeaderData = character.getCountryLeaderData(); countryLeaderData.has_value())
	{
		out << *countryLeaderData;
	}

	if (const auto& commanderData = character.getCommanderData(); commanderData.has_value())
	{
		out << *commanderData;
	}

	if (const auto& admiralData = character.getAdmiralData(); admiralData.has_value())
	{
		out << *admiralData;
	}

	out << "\t}\n";

	return out;
}