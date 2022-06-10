#include "src/OutHoi4/Ideologies/OutIdeology.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Ideology& ideology)
{
	out << "\t" << ideology.ideologyName << " = {\n";
	out << "\t\n";
	out << "\t\ttypes = {\n";
	out << "\t";
	for (const auto& type: ideology.types)
	{
		out << "\t\t\n";
		out << "\t\t\t" << type << " = {\n";
		out << "\t\t\t}\n";
	}
	out << "\t\t}\n";
	out << "\t\t\n";
	out << "\t\tdynamic_faction_names = {\n";
	for (const auto& dynamicFactionName: ideology.dynamicFactionNames)
	{
		out << "\t\t\t\"" << dynamicFactionName << "\"\n";
	}
	out << "\t\t}\n";
	out << "\t\t\n";
	out << "\t\tcolor " << *ideology.theColor << "\n";
	out << "\t\t\n";
	out << "\t\trules = {\n";
	for (const auto& rule: ideology.rules)
	{
		out << "\t\t\t" << rule.first << " " << rule.second << "\n";
	}
	out << "\t\t}\n";
	out << "\t\t\n";
	out << "\t\twar_impact_on_world_tension = " << ideology.warImpactOnWorldTension << "\n";
	out << "\t\tfaction_impact_on_world_tension = " << ideology.factionImpactOnWorldTension << "\n";
	out << "\t\t\n";
	out << "\t\tmodifiers = {\n";
	for (const auto& modifier: ideology.modifiers)
	{
		out << "\t\t\t" << modifier.first << " " << modifier.second << "\n";
	}
	out << "\t\t}\n";
	out << "\t\t\n";
	out << "\t\tfaction_modifiers = {\n";
	for (const auto& factionModifier: ideology.factionModifiers)
	{
		out << "\t\t\t" << factionModifier.first << " " << factionModifier.second << "\n";
	}
	out << "\t\t}\n";
	if (!ideology.cans.empty())
	{
		out << "\n";
	}
	for (const auto& can: ideology.cans)
	{
		out << "\t\t" << can.first << " = " << can.second << "\n";
	}
	if (!ideology.cans.empty())
	{
		out << "\n";
	}
	out << "\t\t" << ideology.AI << " = yes\n";
	out << "\t}\n";
	out << "\n\n\n";

	return out;
}