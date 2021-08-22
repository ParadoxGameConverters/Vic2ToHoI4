#include "GraphicsMapper.h"
#include "GraphicsCultureGroup.h"



std::vector<std::string> Mappers::GraphicsMapper::getArmyPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto armyPortraitMapping = armyPortraitMappings.find(culture);
		 armyPortraitMapping != armyPortraitMappings.end())
	{
		return armyPortraitMapping->second;
	}

	if (const auto armyPortraitMapping = armyPortraitMappings.find(cultureGroup);
		 armyPortraitMapping != armyPortraitMappings.end())
	{
		return armyPortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getNavyPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto navyPortraitMapping = navyPortraitMappings.find(culture);
		 navyPortraitMapping != navyPortraitMappings.end())
	{
		return navyPortraitMapping->second;
	}

	if (const auto navyPortraitMapping = navyPortraitMappings.find(cultureGroup);
		 navyPortraitMapping != navyPortraitMappings.end())
	{
		return navyPortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getMaleMonarchPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto maleMonarchMapping = maleMonarchMappings.find(culture);
		 maleMonarchMapping != maleMonarchMappings.end())
	{
		return maleMonarchMapping->second;
	}

	if (const auto maleMonarchMapping = maleMonarchMappings.find(cultureGroup);
		 maleMonarchMapping != maleMonarchMappings.end())
	{
		return maleMonarchMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemaleMonarchPortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto femaleMonarchMapping = femaleMonarchMappings.find(culture);
		 femaleMonarchMapping != femaleMonarchMappings.end())
	{
		return femaleMonarchMapping->second;
	}

	if (const auto femaleMonarchMapping = femaleMonarchMappings.find(cultureGroup);
		 femaleMonarchMapping != femaleMonarchMappings.end())
	{
		return femaleMonarchMapping->second;
	}

	return {};
}


std::string Mappers::GraphicsMapper::getLeaderPortrait(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& ideology)
{
	auto portraits = getLeaderPortraits(culture, ideology);
	if (!portraits.empty())
	{
		const auto key = std::make_pair(culture, ideology);
		auto index = leaderPortraitIndexes.find(key);
		if (index == leaderPortraitIndexes.end())
		{
			leaderPortraitIndexes.emplace(key, 0);
			index = leaderPortraitIndexes.find(key);
		}
		auto portrait = portraits[index->second];
		index->second = (index->second + 1) % portraits.size();
		return portrait;
	}

	portraits = getLeaderPortraits(cultureGroup, ideology);
	if (!portraits.empty())
	{
		const auto key = std::make_pair(cultureGroup, ideology);
		auto index = leaderPortraitIndexes.find(key);
		if (index == leaderPortraitIndexes.end())
		{
			leaderPortraitIndexes.emplace(key, 0);
			index = leaderPortraitIndexes.find(key);
		}
		auto portrait = portraits[index->second];
		index->second = (index->second + 1) % portraits.size();
		return portrait;
	}

	return "gfx/leaders/leader_unknown.dds";
}


std::vector<std::string> Mappers::GraphicsMapper::getLeaderPortraits(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& ideology) const
{
	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(culture);
		 leaderPortraitMapping != leaderPortraitMappings.end())
	{
		if (const auto portraits = leaderPortraitMapping->second.find(ideology);
			 portraits != leaderPortraitMapping->second.end())
		{
			return portraits->second;
		}
	}

	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(cultureGroup);
		 leaderPortraitMapping != leaderPortraitMappings.end())
	{
		if (const auto portraits = leaderPortraitMapping->second.find(ideology);
			 portraits != leaderPortraitMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {"gfx/leaders/leader_unknown.dds"};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemalePortraits(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& type) const
{
	if (const auto femaleLeaderMapping = femalePortraitMappings.find(culture);
		 femaleLeaderMapping != femalePortraitMappings.end())
	{
		if (const auto portraits = femaleLeaderMapping->second.find(type); portraits != femaleLeaderMapping->second.end())
		{
			return portraits->second;
		}
	}

	if (const auto femaleLeaderMapping = femalePortraitMappings.find(cultureGroup);
		 femaleLeaderMapping != femalePortraitMappings.end())
	{
		if (const auto portraits = femaleLeaderMapping->second.find(type); portraits != femaleLeaderMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {"gfx/leaders/leader_unknown_female.dds"};
}


std::string Mappers::GraphicsMapper::getIdeologyMinisterPortrait(const std::string& culture,
	 const std::string& cultureGroup,
	 const std::string& ideology)
{
	auto portraits = getIdeologyMinisterPortraits(culture, ideology);
	if (!portraits.empty())
	{
		const auto key = std::make_pair(culture, ideology);
		auto index = ministerPortraitIndexes.find(key);
		if (index == ministerPortraitIndexes.end())
		{
			ministerPortraitIndexes.emplace(key, 0);
			index = ministerPortraitIndexes.find(key);
		}
		auto portrait = portraits[index->second];
		index->second = (index->second + 1) % portraits.size();
		return portrait;
	}

	portraits = getIdeologyMinisterPortraits(cultureGroup, ideology);
	if (!portraits.empty())
	{
		const auto key = std::make_pair(cultureGroup, ideology);
		auto index = ministerPortraitIndexes.find(key);
		if (index == ministerPortraitIndexes.end())
		{
			ministerPortraitIndexes.emplace(key, 0);
			index = ministerPortraitIndexes.find(key);
		}
		auto portrait = portraits[index->second];
		index->second = (index->second + 1) % portraits.size();
		return portrait;
	}

	return "gfx/interface/ideas/idea_unknown.dds";
}


std::vector<std::string> Mappers::GraphicsMapper::getLeaderPortraits(const std::string& cultureOrGroup,
	 const std::string& ideology) const
{
	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(cultureOrGroup);
		 leaderPortraitMapping != leaderPortraitMappings.end())
	{
		if (const auto portraits = leaderPortraitMapping->second.find(ideology);
			 portraits != leaderPortraitMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getIdeologyMinisterPortraits(const std::string& cultureOrGroup,
	 const std::string& ideology) const
{
	if (const auto ideologyMinisterMapping = ideologyMinisterMappings.find(cultureOrGroup);
		 ideologyMinisterMapping != ideologyMinisterMappings.end())
	{
		if (const auto portraits = ideologyMinisterMapping->second.find(ideology);
			 portraits != ideologyMinisterMapping->second.end())
		{
			return portraits->second;
		}
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getMaleOperativePortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto operativePortraitMapping = maleOperativeMappings.find(culture);
		 operativePortraitMapping != maleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	if (const auto operativePortraitMapping = maleOperativeMappings.find(cultureGroup);
		 operativePortraitMapping != maleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemaleOperativePortraits(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto operativePortraitMapping = femaleOperativeMappings.find(culture);
		 operativePortraitMapping != femaleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	if (const auto operativePortraitMapping = femaleOperativeMappings.find(cultureGroup);
		 operativePortraitMapping != femaleOperativeMappings.end())
	{
		return operativePortraitMapping->second;
	}

	return {};
}


std::optional<std::string> Mappers::GraphicsMapper::getGraphicalCulture(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto graphicalCulture = graphicalCultureMap.find(culture); graphicalCulture != graphicalCultureMap.end())
	{
		return graphicalCulture->second;
	}

	if (const auto graphicalCulture = graphicalCultureMap.find(cultureGroup);
		 graphicalCulture != graphicalCultureMap.end())
	{
		return graphicalCulture->second;
	}

	return std::nullopt;
}


std::optional<std::string> Mappers::GraphicsMapper::get2dGraphicalCulture(const std::string& culture,
	 const std::string& cultureGroup) const
{
	if (const auto graphicalCulture2d = graphicalCulture2dMap.find(culture);
		 graphicalCulture2d != graphicalCulture2dMap.end())
	{
		return graphicalCulture2d->second;
	}

	if (const auto graphicalCulture2d = graphicalCulture2dMap.find(cultureGroup);
		 graphicalCulture2d != graphicalCulture2dMap.end())
	{
		return graphicalCulture2d->second;
	}

	return std::nullopt;
}