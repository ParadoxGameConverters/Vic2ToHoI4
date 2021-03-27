#include "GraphicsMapper.h"
#include "GraphicsCultureGroup.h"



std::vector<std::string> Mappers::GraphicsMapper::getArmyPortraits(const std::string& cultureGroup) const
{
	if (const auto armyPortraitMapping = armyPortraitMappings.find(cultureGroup);
		 armyPortraitMapping != armyPortraitMappings.end())
	{
		return armyPortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getNavyPortraits(const std::string& cultureGroup) const
{
	if (const auto navyPortraitMapping = navyPortraitMappings.find(cultureGroup);
		 navyPortraitMapping != navyPortraitMappings.end())
	{
		return navyPortraitMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getMaleMonarchPortraits(const std::string& cultureGroup) const
{
	if (const auto maleMonarchMapping = maleMonarchMappings.find(cultureGroup);
		 maleMonarchMapping != maleMonarchMappings.end())
	{
		return maleMonarchMapping->second;
	}

	return {};
}


std::vector<std::string> Mappers::GraphicsMapper::getFemaleMonarchPortraits(const std::string& cultureGroup) const
{
	if (const auto femaleMonarchMapping = femaleMonarchMappings.find(cultureGroup);
		 femaleMonarchMapping != femaleMonarchMappings.end())
	{
		return femaleMonarchMapping->second;
	}

	return {};
}


std::string Mappers::GraphicsMapper::getLeaderPortrait(const std::string& cultureGroup, const std::string& ideology)
{
	auto portraits = getLeaderPortraits(cultureGroup, ideology);
	if (!portraits.empty())
	{
		auto portrait = portraits[leaderPortraitIndex];
		leaderPortraitIndex = leaderPortraitIndex + 1 / static_cast<int>(portraits.size());
		return portrait;
	}

	return "gfx/leaders/leader_unknown.dds";
}


std::vector<std::string> Mappers::GraphicsMapper::getLeaderPortraits(const std::string& cultureGroup,
	 const std::string& ideology) const
{
	if (const auto leaderPortraitMapping = leaderPortraitMappings.find(cultureGroup);
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


std::string Mappers::GraphicsMapper::getIdeologyMinisterPortrait(const std::string& cultureGroup,
	 const std::string& ideology)
{
	auto portraits = getIdeologyMinisterPortraits(cultureGroup, ideology);
	if (!portraits.empty())
	{
		auto portrait = portraits[ministerPortraitIndex];
		ministerPortraitIndex = ministerPortraitIndex + 1 / static_cast<int>(portraits.size());
		return portrait;
	}

	return "gfx/interface/ideas/idea_unknown.dds";
}


std::vector<std::string> Mappers::GraphicsMapper::getIdeologyMinisterPortraits(const std::string& cultureGroup,
	 const std::string& ideology) const
{
	if (const auto ideologyMinisterMapping = ideologyMinisterMappings.find(cultureGroup);
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


std::optional<std::string> Mappers::GraphicsMapper::getGraphicalCulture(const std::string& cultureGroup) const
{
	if (const auto graphicalCulture = graphicalCultureMap.find(cultureGroup);
		 graphicalCulture != graphicalCultureMap.end())
	{
		return graphicalCulture->second;
	}

	return std::nullopt;
}


std::optional<std::string> Mappers::GraphicsMapper::get2dGraphicalCulture(const std::string& cultureGroup) const
{
	if (const auto graphicalCulture2d = graphicalCulture2dMap.find(cultureGroup);
		 graphicalCulture2d != graphicalCulture2dMap.end())
	{
		return graphicalCulture2d->second;
	}

	return std::nullopt;
}