#include "src/OutHoi4/Map/OutStrategicRegions.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Map/OutStrategicRegion.h"
#include <ranges>



void HoI4::outputStrategicRegions(const StrategicRegions& strategicRegions, const std::string& outputName)
{
	if (!commonItems::TryCreateFolder("output/" + outputName + "/map/strategicregions"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/map/strategicregions");
	}
	for (const auto& strategicRegion: strategicRegions.getStrategicRegions() | std::views::values)
	{
		outputStrategicRegion(strategicRegion, "output/" + outputName + "/map/strategicregions/");
	}
}
