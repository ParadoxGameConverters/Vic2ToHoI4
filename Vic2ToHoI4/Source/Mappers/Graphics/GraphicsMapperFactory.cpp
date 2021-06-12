#include "GraphicsMapperFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"
#include <algorithm>
#include <random>



Mappers::GraphicsMapper::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureGroupName, std::istream& theStream) {
		const auto newCultureGroup = graphicsCultureGroupFactory.importCultureGroup(theStream);
		graphicsMapper->armyPortraitMappings[cultureGroupName] = newCultureGroup->getArmyPortraits();
		graphicsMapper->navyPortraitMappings[cultureGroupName] = newCultureGroup->getNavyPortraits();
		graphicsMapper->maleMonarchMappings[cultureGroupName] = newCultureGroup->getMaleMonarchPortraits();
		graphicsMapper->femaleMonarchMappings[cultureGroupName] = newCultureGroup->getFemaleMonarchPortraits();
		graphicsMapper->graphicalCultureMap[cultureGroupName] = newCultureGroup->getGraphicalCulture();
		graphicsMapper->graphicalCulture2dMap[cultureGroupName] = newCultureGroup->getGraphicalCulture2D();
		graphicsMapper->maleOperativeMappings[cultureGroupName] = newCultureGroup->getMaleOperativePortraits();
		graphicsMapper->femaleOperativeMappings[cultureGroupName] = newCultureGroup->getFemaleOperativePortraits();
		loadLeaderPortraitMappings(cultureGroupName, newCultureGroup->getLeaderPortraits());
		loadIdeologyMinisterPortraitMappings(cultureGroupName, newCultureGroup->getIdeologyMinisterPortraits());
	});
}


std::unique_ptr<Mappers::GraphicsMapper> Mappers::GraphicsMapper::Factory::importGraphicsMapper()
{
	Log(LogLevel::Info) << "\tReading graphics mappings";

	graphicsMapper = std::make_unique<GraphicsMapper>();
	parseFile("Configurables/cultureGroupToGraphics.txt");
	return std::move(graphicsMapper);
}


void Mappers::GraphicsMapper::Factory::loadLeaderPortraitMappings(const std::string& cultureGroup,
	 const std::map<std::string, std::vector<std::string>>& portraitMappings)
{
	auto cultureGroupMappings = graphicsMapper->leaderPortraitMappings.find(cultureGroup);
	if (cultureGroupMappings == graphicsMapper->leaderPortraitMappings.end())
	{
		cultureGroupToPortraitsMap newCultureGroupMappings;
		graphicsMapper->leaderPortraitMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = graphicsMapper->leaderPortraitMappings.find(cultureGroup);
	}

	for (const auto& portraitMapping: portraitMappings)
	{
		cultureGroupMappings->second.insert(portraitMapping);
	}
}


void Mappers::GraphicsMapper::Factory::loadIdeologyMinisterPortraitMappings(const std::string& cultureGroup,
	 const std::map<std::string, std::vector<std::string>>& portraitMappings)
{
	auto cultureGroupMappings = graphicsMapper->ideologyMinisterMappings.find(cultureGroup);
	if (cultureGroupMappings == graphicsMapper->ideologyMinisterMappings.end())
	{
		cultureGroupToPortraitsMap newCultureGroupMappings;
		graphicsMapper->ideologyMinisterMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = graphicsMapper->ideologyMinisterMappings.find(cultureGroup);
	}

	for (const auto& portraitMapping: portraitMappings)
	{
		cultureGroupMappings->second.insert(portraitMapping);
	}
}