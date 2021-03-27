#include "GraphicsMapper.h"
#include "CommonRegexes.h"
#include "GraphicsCultureGroup.h"
#include "Log.h"
#include "ParserHelpers.h"



void graphicsMapper::init()
{
	Log(LogLevel::Info) << "\tReading graphics mappings";

	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureGroupName, std::istream& theStream) {
		const auto newCultureGroup = graphicsCultureGroupFactory.importCultureGroup(theStream);
		armyPortraitMappings[cultureGroupName] = newCultureGroup->getArmyPortraits();
		navyPortraitMappings[cultureGroupName] = newCultureGroup->getNavyPortraits();
		maleMonarchMappings[cultureGroupName] = newCultureGroup->getMaleMonarchPortraits();
		femaleMonarchMappings[cultureGroupName] = newCultureGroup->getFemaleMonarchPortraits();
		graphicalCultureMap[cultureGroupName] = newCultureGroup->getGraphicalCulture();
		graphicalCulture2dMap[cultureGroupName] = newCultureGroup->getGraphicalCulture2D();
		loadLeaderPortraitMappings(cultureGroupName, newCultureGroup->getLeaderPortraits());
		loadIdeologyMinisterPortraitMappings(cultureGroupName, newCultureGroup->getIdeologyMinisterPortraits());
	});

	parseFile("Configurables/cultureGroupToGraphics.txt");
}


void graphicsMapper::loadLeaderPortraitMappings(const std::string& cultureGroup,
	 const std::map<std::string, std::vector<std::string>>& portraitMappings)
{
	auto cultureGroupMappings = leaderPortraitMappings.find(cultureGroup);
	if (cultureGroupMappings == leaderPortraitMappings.end())
	{
		cultureGroupToPortraitsMap newCultureGroupMappings;
		leaderPortraitMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = leaderPortraitMappings.find(cultureGroup);
	}

	for (auto portraitMapping: portraitMappings)
	{
		cultureGroupMappings->second.insert(portraitMapping);
	}
}


void graphicsMapper::loadIdeologyMinisterPortraitMappings(const std::string& cultureGroup,
	 const std::map<std::string, std::vector<std::string>>& portraitMappings)
{
	auto cultureGroupMappings = ideologyMinisterMappings.find(cultureGroup);
	if (cultureGroupMappings == ideologyMinisterMappings.end())
	{
		cultureGroupToPortraitsMap newCultureGroupMappings;
		ideologyMinisterMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = ideologyMinisterMappings.find(cultureGroup);
	}

	for (auto portraitMapping: portraitMappings)
	{
		cultureGroupMappings->second.insert(portraitMapping);
	}
}


const std::vector<std::string> graphicsMapper::getArmyPortraits(const std::string& cultureGroup)
{
	auto mapping = armyPortraitMappings.find(cultureGroup);
	if (mapping == armyPortraitMappings.end())
	{
		return {};
	}

	return mapping->second;
}


const std::vector<std::string> graphicsMapper::getNavyPortraits(const std::string& cultureGroup)
{
	auto mapping = navyPortraitMappings.find(cultureGroup);
	if (mapping == navyPortraitMappings.end())
	{
		return {};
	}

	return mapping->second;
}


const std::vector<std::string> graphicsMapper::getMaleMonarchPortraits(const std::string& cultureGroup) const
{
	auto mapping = maleMonarchMappings.find(cultureGroup);
	if (mapping == maleMonarchMappings.end())
	{
		return {};
	}

	return mapping->second;
}


const std::vector<std::string> graphicsMapper::getFemaleMonarchPortraits(const std::string& cultureGroup) const
{
	auto mapping = femaleMonarchMappings.find(cultureGroup);
	if (mapping == femaleMonarchMappings.end())
	{
		return {};
	}

	return mapping->second;
}


std::string graphicsMapper::getLeaderPortrait(const std::string& cultureGroup, const std::string& ideology)
{
	if (auto portraits = getLeaderPortraits(cultureGroup, ideology))
	{
		std::uniform_int_distribution<int> firstNameGen(0, static_cast<int>(portraits->size()) - 1);
		return (*portraits)[firstNameGen(rng)];
	}
	else
	{
		return "gfx/leaders/leader_unknown.dds";
	}
}


std::optional<std::vector<std::string>> graphicsMapper::getLeaderPortraits(const std::string& cultureGroup,
	 const std::string& ideology) const
{
	if (auto mapping = leaderPortraitMappings.find(cultureGroup); mapping != leaderPortraitMappings.end())
	{
		if (auto portraits = mapping->second.find(ideology); portraits != mapping->second.end())
		{
			return portraits->second;
		}
	}

	return {};
}


std::string graphicsMapper::getIdeologyMinisterPortrait(const std::string& cultureGroup, const std::string& ideology)
{
	auto portraits = getIdeologyMinisterPortraits(cultureGroup, ideology);

	if (portraits)
	{
		std::uniform_int_distribution<int> firstNameGen(0, static_cast<int>(portraits->size()) - 1);
		return (*portraits)[firstNameGen(rng)];
	}
	else
	{
		return "gfx/interface/ideas/idea_unknown.dds";
	}
}


std::string graphicsMapper::getGeneralPortrait(const std::string& cultureGroup) const
{
	return "";
}


std::optional<std::vector<std::string>> graphicsMapper::getIdeologyMinisterPortraits(const std::string& cultureGroup,
	 const std::string& ideology) const
{
	if (auto mapping = ideologyMinisterMappings.find(cultureGroup); mapping != ideologyMinisterMappings.end())
	{
		if (auto portraits = mapping->second.find(ideology); portraits != mapping->second.end())
		{
			return portraits->second;
		}
	}

	return {};
}


std::optional<std::string> graphicsMapper::getGraphicalCulture(const std::string& cultureGroup) const
{
	if (auto itr = graphicalCultureMap.find(cultureGroup); itr != graphicalCultureMap.end())
	{
		return itr->second;
	}
	else
	{
		return {};
	}
}


std::optional<std::string> graphicsMapper::get2dGraphicalCulture(const std::string& cultureGroup) const
{
	if (auto itr = graphicalCulture2dMap.find(cultureGroup); itr != graphicalCulture2dMap.end())
	{
		return itr->second;
	}
	else
	{
		return {};
	}
}