/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "Technologies.h"



HoI4::technologies::technologies(
	const mappers::techMapper& theTechMapper,
	const std::set<std::string>& oldTechs,
	const std::set<std::string>& oldInventions
)
{
	for (auto techMapping: theTechMapper.getAllTechMappings())
	{
		if ((oldTechs.count(techMapping.first) > 0) || (oldInventions.count(techMapping.first) > 0))
		{
			for (auto HoI4Tech: techMapping.second)
			{
				mainTechnologies.insert(HoI4Tech);
			}
		}
	}

	for (auto techMapping: theTechMapper.getAllNonMtgNavalTechMappings())
	{
		if ((oldTechs.count(techMapping.first) > 0) || (oldInventions.count(techMapping.first) > 0))
		{
			for (auto HoI4Tech: techMapping.second)
			{
				nonMtgNavalTechnologies.insert(HoI4Tech);
			}
		}
	}

	for (auto techMapping: theTechMapper.getAllMtgNavalTechMappings())
	{
		if ((oldTechs.count(techMapping.first) > 0) || (oldInventions.count(techMapping.first) > 0))
		{
			for (auto HoI4Tech: techMapping.second)
			{
				mtgNavalTechnologies.insert(HoI4Tech);
			}
		}
	}

	for (auto bonusMapping: theTechMapper.getAllResearchBonuses())
	{
		if ((oldTechs.count(bonusMapping.first) > 0) || (oldInventions.count(bonusMapping.first) > 0))
		{
			for (auto bonus: bonusMapping.second)
			{
				setResearchBonus(bonus.first, bonus.second);
			}
		}
	}
}


void HoI4::technologies::setResearchBonus(const std::string& tech, int bonus)
{
	std::map<std::string, int>::iterator researchBonusEntry = researchBonuses.find(tech);
	if ((researchBonusEntry == researchBonuses.end()) || (researchBonusEntry->second < bonus))
	{
		researchBonuses[tech] = bonus;
	}
}


bool HoI4::technologies::hasTechnology(std::string technology) const
{
	return (mainTechnologies.count(technology) > 0) || (nonMtgNavalTechnologies.count(technology) > 0) || (mtgNavalTechnologies.count(technology) > 0);
}


void HoI4::technologies::outputTechnology(std::ostream& output) const
{
	output << "# Starting tech\n";
	output << "set_technology = {\n";
	for (auto technology: mainTechnologies)
	{
		output << "\t" << technology << " = 1\n";
	}
	output << "}\n";
	output << "\n";
	output << "if = {\n";
	output << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	output << "\tset_technology = {\n";
	for (auto technology: nonMtgNavalTechnologies)
	{
		output << "\t\t" << technology << " = 1\n";
	}
	output << "\t}\n";
	output << "}\n";
	output << "if = {\n";
	output << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	output << "\tset_technology = {\n";
	for (auto technology: mtgNavalTechnologies)
	{
		output << "\t\t" << technology << " = 1\n";
	}
	output << "\t}\n";
	output << "}\n";
}


void HoI4::technologies::outputResearchBonuses(std::ostream& output) const
{
	output << "# Research Bonuses\n";
	for (auto researchBonus : researchBonuses)
	{
		std::string name = researchBonus.first.substr(0, researchBonus.first.size() - 5) + "_bonus";
		output << "add_tech_bonus = { name = " << name << " bonus = 0." << float(researchBonus.second) << " uses = 1 category = " << researchBonus.first << " }\n";
	}
}