#include "src/HOI4World/Map/StrategicRegion.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/MapRegion.h"
#include <fstream>



HoI4::StrategicRegion::StrategicRegion(const std::filesystem::path& filename, const Configuration& theConfiguration):
	 filename_(filename)
{
	registerKeyword("strategic_region", [this](std::istream& theStream) {
		MapRegion theRegion(theStream);
		ID = theRegion.getID();
		name = theRegion.takeName();
		oldProvinces = theRegion.takeProvinces();
		navalTerrain = theRegion.takeNavalTerrain();
		staticModifiers = theRegion.takeStaticModifiers();
		weather = theRegion.takeWeather();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(theConfiguration.getHoI4Path() / "map/strategicregions" / filename);
	clearRegisteredKeywords();
}