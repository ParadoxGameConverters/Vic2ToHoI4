#include "src/OutHoi4/Factions/OutFactionTemplate.h"



std::ostream& HoI4::operator<<(std::ostream& out, const FactionTemplate& theTemplate)
{
	out << theTemplate.id << " = {\n";
	out << "\tname = " << theTemplate.name << "\n";
	out << "\ticon = " << theTemplate.icon << "\n";
	out << "\tmanifest = " << theTemplate.manifest << "\n";

	out << "\tgoals = {\n";
	for (const auto& goal: theTemplate.goals)
	{
		out << "\t\t" << goal << "\n";
	}
	out << "\t}\n";

	out << "\tdefault_rules = {\n";
	for (const auto& rule: theTemplate.rules)
	{
		out << "\t\t" << rule << "\n";
	}
	out << "\t}\n";
	out << "}\n";

	return out;
}