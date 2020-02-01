#include "../../Configuration.h"
#include "Region.h"
#include "StrategicRegion.h"
#include "newParser.h"
#include <fstream>



HoI4::StrategicRegion::StrategicRegion(const std::string& _filename):
	filename(_filename)
{
	registerKeyword("strategic_region", [this](const std::string& unused, std::istream& theStream){
		const Region theRegion(theStream);
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