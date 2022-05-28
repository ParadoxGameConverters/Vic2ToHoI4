#include "StrategicRegion.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "MapRegion.h"
#include "ParserHelpers.h"
#include <fstream>



HoI4::StrategicRegion::StrategicRegion(const std::string& _filename, const Configuration& theConfiguration):
	 filename(_filename)
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

	parseFile(theConfiguration.getHoI4Path() + "/map/strategicregions/" + _filename);
	clearRegisteredKeywords();
}