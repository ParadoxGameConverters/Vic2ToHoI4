#include "OutStrategicRegions.h"
#include "OSCompatibilityLayer.h"
#include "OutStrategicRegion.h"



void HoI4::outputStrategicRegions(const StrategicRegions& strategicRegions, const std::string& outputName)
{
	if (!Utils::TryCreateFolder("output/" + outputName + "/map/strategicregions"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/map/strategicregions");
	}
	for (const auto& strategicRegion: strategicRegions.getStrategicRegions())
	{
		outputStrategicRegion(strategicRegion.second, "output/" + outputName + "/map/strategicregions/");
	}
}
