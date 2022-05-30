#include "OutWar.h"



std::ostream& HoI4::operator<<(std::ostream& out, const War& theWar)
{
	out << "declare_war_on = {\n";
	out << "\ttarget = " << theWar.originalDefender << "\n";
	out << "\ttype = " << theWar.CB << "\n";
	if (theWar.state)
	{
		out << "\tgenerator = { " << *theWar.state << " }\n";
	}
	out << "}\n";
	if (theWar.CB == "civil_war")
	{
		out << "add_civil_war_target = " << theWar.originalDefender << "\n";
	}

	for (const auto& extraAttacker: theWar.extraAttackers)
	{
		out << extraAttacker << " = {\n";
		out << "\tadd_to_war = {\n";
		out << "\t\ttargeted_alliance = " << theWar.originalAttacker << "\n";
		out << "\t\tenemy = " << theWar.originalDefender << "\n";
		out << "\t}\n";
		out << "}\n";
	}

	for (const auto& extraDefender: theWar.extraDefenders)
	{
		out << extraDefender << " = {\n";
		out << "\tadd_to_war = {\n";
		out << "\t\ttargeted_alliance = " << theWar.originalDefender << "\n";
		out << "\t\tenemy = " << theWar.originalAttacker << "\n";
		out << "\t}\n";
		out << "}\n";
	}

	out << "\n";

	return out;
}