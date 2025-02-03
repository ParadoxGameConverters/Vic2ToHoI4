#include "src/OutHoi4/Map/OutSupplyZones.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Map/OutSupplyZone.h"



void HoI4::outputSupplyZones(const SupplyZones& supplyZones, const std::filesystem::path& outputName)
{
	std::filesystem::path folder = "output" / outputName / "map/supplyareas";
	if (!std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	for (const auto& zone: supplyZones.getSupplyZones())
	{
		if (auto possibleFileName = supplyZones.getSupplyZoneFileName(zone.first))
		{
			outputSupplyZone(zone.second, *possibleFileName, outputName);
		}
	}
}