#include "OutTechnologies.h"



void HoI4::outputTechnology(const technologies& theTechnologies, std::ostream& output)
{
	output << "# Starting tech\n";
	output << "set_technology = {\n";
	for (auto technology: theTechnologies.getMainTechnologies())
	{
		output << "\t" << technology << " = 1\n";
	}
	output << "}\n";
	output << "\n";
	output << "if = {\n";
	output << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	output << "\tset_technology = {\n";
	for (auto technology: theTechnologies.getNonMtgNavalTechnologies())
	{
		output << "\t\t" << technology << " = 1\n";
	}
	output << "\t}\n";
	output << "}\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	output << "\tset_technology = {\n";
	for (auto technology: theTechnologies.getMtgNavalTechnologies())
	{
		output << "\t\t" << technology << " = 1\n";
	}
	output << "\t}\n";
	output << "}\n";
}


void HoI4::outputResearchBonuses(const technologies& theTechnologies, std::ostream& output)
{
	output << "# Research Bonuses\n";
	for (auto researchBonus: theTechnologies.getResearchBonuses())
	{
		std::string name = researchBonus.first.substr(0, researchBonus.first.size() - 5) + "_bonus";
		output << "add_tech_bonus = { name = " << name << " bonus = 0." << float(researchBonus.second)
				 << " uses = 1 category = " << researchBonus.first << " }\n";
	}
}