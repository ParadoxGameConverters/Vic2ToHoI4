#include "RegionsFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"



HoI4::Regions::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& regionId, std::istream& theStream) {
		const auto region = regionFactory.importRegion(theStream);
		for (const auto province: region->getProvinces())
		{
			if (theRegions->regionsMap.contains(province))
			{
				Log(LogLevel::Warning) << "Province " << province << " was assigned to multiple regions";
			}
			theRegions->regionsMap.emplace(province, regionId);
		}
		theRegions->regionNames.emplace(regionId, region->getName());
		theRegions->regionAdjectives.emplace(regionId, region->getAdjective());
		theRegions->regionLevels.emplace(regionId, region->getLevel());
	});
}


std::unique_ptr<HoI4::Regions> HoI4::Regions::Factory::getRegions()
{
	theRegions = std::make_unique<Regions>();

	parseFile("./Configurables/Map/regions.txt");

	return std::move(theRegions);
}