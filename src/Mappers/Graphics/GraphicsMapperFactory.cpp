#include "src/Mappers/Graphics/GraphicsMapperFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include <algorithm>
#include <random>



Mappers::GraphicsMapper::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& mappingName, std::istream& theStream) {
		const auto newCultureGroup = graphicsCultureGroupFactory.importCultureGroup(theStream);

		const auto& cultureGroups = newCultureGroup->getCulturesAndGroups();
		if (cultureGroups.empty())
		{
			loadMappings(mappingName, *newCultureGroup);
		}
		for (const auto& cultureGroup: cultureGroups)
		{
			loadMappings(cultureGroup, *newCultureGroup);
		}
	});
}


std::unique_ptr<Mappers::GraphicsMapper> Mappers::GraphicsMapper::Factory::importGraphicsMapper()
{
	Log(LogLevel::Info) << "\tReading graphics mappings";

	graphicsMapper = std::make_unique<GraphicsMapper>();
	parseFile(std::filesystem::path("Configurables/cultureGroupToGraphics.txt"));
	return std::move(graphicsMapper);
}


void Mappers::GraphicsMapper::Factory::loadMappings(const std::string& cultureGroupName,
	 const GraphicsCultureGroup& graphicsCultureGroup)
{
	graphicsMapper->armyPortraitMappings[cultureGroupName] = graphicsCultureGroup.getArmyPortraits();
	graphicsMapper->navyPortraitMappings[cultureGroupName] = graphicsCultureGroup.getNavyPortraits();
	graphicsMapper->maleMonarchMappings[cultureGroupName] = graphicsCultureGroup.getMaleMonarchPortraits();
	graphicsMapper->femaleMonarchMappings[cultureGroupName] = graphicsCultureGroup.getFemaleMonarchPortraits();
	graphicsMapper->graphicalCultureMap[cultureGroupName] = graphicsCultureGroup.getGraphicalCulture();
	graphicsMapper->graphicalCulture2dMap[cultureGroupName] = graphicsCultureGroup.getGraphicalCulture2D();
	graphicsMapper->maleOperativeMappings[cultureGroupName] = graphicsCultureGroup.getMaleOperativePortraits();
	graphicsMapper->femaleOperativeMappings[cultureGroupName] = graphicsCultureGroup.getFemaleOperativePortraits();
	loadLeaderPortraitMappings(cultureGroupName, graphicsCultureGroup.getLeaderPortraits());
	loadFemalePortraitMappings(cultureGroupName, graphicsCultureGroup.getFemalePortraits());
	loadIdeologyMinisterPortraitMappings(cultureGroupName, graphicsCultureGroup.getIdeologyMinisterPortraits());
}


void Mappers::GraphicsMapper::Factory::loadLeaderPortraitMappings(const std::string& cultureGroup,
	 const std::map<std::string, std::vector<std::string>>& portraitMappings)
{
	auto cultureGroupMappings = graphicsMapper->leaderPortraitMappings.find(cultureGroup);
	if (cultureGroupMappings == graphicsMapper->leaderPortraitMappings.end())
	{
		culturesAndGroupsToPortraitsMap newCultureGroupMappings;
		graphicsMapper->leaderPortraitMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = graphicsMapper->leaderPortraitMappings.find(cultureGroup);
	}

	for (const auto& portraitMapping: portraitMappings)
	{
		cultureGroupMappings->second.insert(portraitMapping);
	}
}

void Mappers::GraphicsMapper::Factory::loadFemalePortraitMappings(const std::string& cultureGroup,
	 const std::map<std::string, std::vector<std::string>>& portraitMappings)
{
	auto cultureGroupMappings = graphicsMapper->femalePortraitMappings.find(cultureGroup);
	if (cultureGroupMappings == graphicsMapper->femalePortraitMappings.end())
	{
		culturesAndGroupsToPortraitsMap newCultureGroupMappings;
		graphicsMapper->femalePortraitMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = graphicsMapper->femalePortraitMappings.find(cultureGroup);
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
		culturesAndGroupsToPortraitsMap newCultureGroupMappings;
		graphicsMapper->ideologyMinisterMappings.insert(make_pair(cultureGroup, newCultureGroupMappings));
		cultureGroupMappings = graphicsMapper->ideologyMinisterMappings.find(cultureGroup);
	}

	for (const auto& portraitMapping: portraitMappings)
	{
		cultureGroupMappings->second.insert(portraitMapping);
	}
}