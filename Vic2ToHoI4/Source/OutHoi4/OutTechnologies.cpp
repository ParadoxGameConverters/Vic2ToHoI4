#include "OutTechnologies.h"
#include <ostream>



void HoI4::outputTechnology(const technologies& theTechnologies, std::ostream& output)
{
	const auto& technologiesByLimit = theTechnologies.getTechnologies();

	output << "# Starting tech\n";

	// technologies with no limit have a different output format, so handle them separately
	if (const auto& noLimitTechs = technologiesByLimit.find(""); noLimitTechs != technologiesByLimit.end())
	{
		output << "set_technology = {\n";
		for (const auto& technology: noLimitTechs->second)
		{
			output << "\t" << technology << " = 1\n";
		}
		output << "}\n";
		output << "\n";
	}

	for (const auto& [limit, technologies]: technologiesByLimit)
	{
		if (limit.empty()) // no limit techs are handled above
		{
			continue;
		}
		if (technologies.empty())
		{
			continue;
		}
		output << "if = {\n";
		output << "\tlimit = { " << limit << " }\n";
		output << "\tset_technology = {\n";
		for (const auto& technology: technologies)
		{
			output << "\t\t" << technology << " = 1\n";
		}
		output << "\t}\n";
		output << "}\n";
		output << "\n";
	}
}


void HoI4::outputResearchBonuses(const technologies& theTechnologies, std::ostream& output)
{
	output << "# Research Bonuses\n";
	for (const auto& researchBonus: theTechnologies.getResearchBonuses())
	{
		auto name = researchBonus.first.substr(0, researchBonus.first.size() - 5) + "_bonus";
		output << "add_tech_bonus = { name = " << name << " bonus = " << researchBonus.second
				 << " uses = 1 category = " << researchBonus.first << " }\n";
	}
}