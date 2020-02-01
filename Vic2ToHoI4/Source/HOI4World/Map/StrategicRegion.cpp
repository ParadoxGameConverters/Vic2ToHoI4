#include "../../Configuration.h"
#include "Region.h"
#include "StrategicRegion.h"
#include "ParserHelpers.h"
#include <fstream>



HoI4::StrategicRegion::StrategicRegion(const std::string& _filename):
	filename(_filename)
{
	registerKeyword("strategic_region", [this](const std::string& unused, std::istream& theStream){
		Region theRegion(theStream);
		ID = theRegion.getID();
		name = theRegion.takeName();
		oldProvinces = theRegion.takeProvinces();
		navalTerrain = theRegion.takeNavalTerrain();
		staticModifiers = theRegion.takeStaticModifiers();
		weather = theRegion.takeWeather();
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseFile(theConfiguration.getHoI4Path() + "/map/strategicregions/" + _filename);
	clearRegisteredKeywords();
}