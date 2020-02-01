#include "../../Configuration.h"
#include "HoI4StrategicRegion.h"
#include "Region.h"
#include "Log.h"
#include "newParser.h"
#include "ParserHelpers.h"
#include <fstream>



HoI4StrategicRegion::HoI4StrategicRegion(const std::string& _filename):
	filename(_filename)
{
	registerKeyword("strategic_region", [this](const std::string& unused, std::istream& theStream){
		const HoI4::Region theRegion(theStream);
		ID = theRegion.getID();
		name = theRegion.getName();
		oldProvinces = theRegion.getProvinces();
		navalTerrain = theRegion.getNavalTerrain();
		staticModifiers = theRegion.getStaticModifiers();
		weather = theRegion.getWeather();
	});

	parseFile(theConfiguration.getHoI4Path() + "/map/strategicregions/" + _filename);
	clearRegisteredKeywords();
}