#include "Technologies.h"



HoI4::technologies::technologies(const Mappers::TechMapper& techMapper,
	 const Mappers::ResearchBonusMapper& researchBonusMapper,
	 const std::set<std::string>& oldTechnologiesAndInventions)
{
	for (const auto& techMapping: techMapper.getTechMappings())
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

	for (const auto& bonusMapping: researchBonusMapper.getResearchBonusMappings())
	{
		bool requirementViolated = false;
		for (const auto& requirement: bonusMapping.getVic2Requirements())
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

		for (const auto& bonus: bonusMapping.getResearchBonuses())
		{
			setResearchBonus(bonus.first, bonus.second);
		}
	}
}


int HoI4::technologies::getTechnologyCount() const
{
	int totalTechnologies = 0;
	for (const auto& [unused, technologies]: technologiesByLimits)
	{
		totalTechnologies += static_cast<int>(technologies.size());
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