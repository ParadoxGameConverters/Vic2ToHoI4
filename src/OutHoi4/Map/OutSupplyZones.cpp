#include "src/OutHoi4/Map/OutSupplyZones.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/Map/OutSupplyZone.h"



void HoI4::outputSupplyZones(const SupplyZones& supplyZones, const std::string& outputName)
{
	if (!commonItems::TryCreateFolder("output/" + outputName + "/map/supplyareas"))
	{
		throw std::runtime_error("Could not create \"output/" + outputName + "/map/supplyareas");
	}

	for (const auto& zone: supplyZones.getSupplyZones())
	{
		if (auto possibleFileName = supplyZones.getSupplyZoneFileName(zone.first))
		{
			outputSupplyZone(zone.second, *possibleFileName, outputName);
		}
	}
}