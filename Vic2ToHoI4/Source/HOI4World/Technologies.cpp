#include "Technologies.h"



HoI4::technologies::technologies(const mappers::techMapper& theTechMapper,
	 const std::set<std::string>& oldTechnologiesAndInventions)
{
	for (const auto& [requirement, techMapping]: theTechMapper.getAllTechMappings())
	{
		if (oldTechnologiesAndInventions.contains(requirement))
		{
			for (const auto& [limit, technologies]: techMapping)
			{
				for (const auto& technology: technologies)
				{
					auto [itr, inserted] = technologiesByLimits.insert(std::make_pair(limit, std::set{technology}));
					if (!inserted)
					{
						itr->second.insert(technology);
					}
				}
			}
		}
	}

	for (const auto& bonusMapping: theTechMapper.getAllResearchBonuses())
	{
		if (oldTechnologiesAndInventions.contains(bonusMapping.first))
		{
			for (const auto& bonus: bonusMapping.second)
			{
				setResearchBonus(bonus.first, bonus.second);
			}
		}
	}
}


int HoI4::technologies::getTechnologyCount() const
{
	int totalTechnologies = 0;
	for (const auto& [unused, technologies]: technologiesByLimits)
	{
		totalTechnologies += technologies.size();
	}

	return totalTechnologies;
}


void HoI4::technologies::setResearchBonus(const std::string& tech, int bonus)
{
	std::map<std::string, int>::iterator researchBonusEntry = researchBonuses.find(tech);
	if ((researchBonusEntry == researchBonuses.end()) || (researchBonusEntry->second < bonus))
	{
		researchBonuses[tech] = bonus;
	}
}


bool HoI4::technologies::hasTechnology(const std::string& technology) const
{
	for (const auto& [unused, technologies]: technologiesByLimits)
	{
		if (technologies.contains(technology))
		{
			return true;
		}
	}

	return false;
}