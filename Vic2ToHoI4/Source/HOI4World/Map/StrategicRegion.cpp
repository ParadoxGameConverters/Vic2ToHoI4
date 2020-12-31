#include "StrategicRegion.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "ParserHelpers.h"
#include "Region.h"
#include <fstream>



HoI4::StrategicRegion::StrategicRegion(const std::string& _filename, const Configuration& theConfiguration):
	 filename(_filename)
{
	registerKeyword("strategic_region", [this](const std::string& unused, std::istream& theStream) {
		Region theRegion(theStream);
		ID = theRegion.getID();
		name = theRegion.takeName();
		oldProvinces = theRegion.takeProvinces();
		navalTerrain = theRegion.takeNavalTerrain();
		staticModifiers = theRegion.takeStaticModifiers();
		weather = theRegion.takeWeather();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(theConfiguration.getHoI4Path() + "/map/strategicregions/" + _filename);
	clearRegisteredKeywords();
}