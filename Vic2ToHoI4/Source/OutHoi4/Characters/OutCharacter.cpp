#include "OutCharacter.h"
#include "OutHoi4/Characters/OutPortrait.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Character& character)
{
	out << "\t" << character.getName() << "={\n";
	out << "\t\tname=" << character.getName() << "\n";
	if (!character.getPortraits().empty())
	{
		out << "\t\tportraits={\n";
		for (const auto& portrait: character.getPortraits())
		{
			out << portrait;
		}
		out << "\t\t}\n";
	}
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

	return out;
}