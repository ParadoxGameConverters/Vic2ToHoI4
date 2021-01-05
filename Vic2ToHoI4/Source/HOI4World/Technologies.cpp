#include "Technologies.h"


#pragma optimize("",off)
HoI4::technologies::technologies(const mappers::techMapper& theTechMapper,
	 const std::set<std::string>& oldTechnologiesAndInventions)
{
	for (const auto& techMapping: theTechMapper.getAllTechMappings())
	{
		bool requirementViolated = false;
		for (const auto& requirement: techMapping.getVic2Requirements())
		{
			if (!oldTechnologiesAndInventions.contains(requirement))
			{
				requirementViolated = true;
				break;
			}
		}
		if (requirementViolated)
		{
			continue;
		}

		const auto& limit = techMapping.getLimit();
		for (const auto& technology: techMapping.getTechs())
		{
			auto [itr, inserted] = technologiesByLimits.insert(std::make_pair(limit, std::set{technology}));
			if (!inserted)
			{
				itr->second.insert(technology);
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
#pragma optimize("", on)

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