#include "src/OutHoi4/Map/OutStrategicRegions.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Map/OutStrategicRegion.h"
#include <ranges>



void HoI4::outputStrategicRegions(const StrategicRegions& strategicRegions, const std::filesystem::path& outputName)
{
	const std::filesystem::path folder = "output" / outputName / "map/strategicregions";
	if (!std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	for (const auto& strategicRegion: strategicRegions.GetStrategicRegions() | std::views::values)
	{
		outputStrategicRegion(strategicRegion, "output" / outputName / "map/strategicregions/");
	}
}
