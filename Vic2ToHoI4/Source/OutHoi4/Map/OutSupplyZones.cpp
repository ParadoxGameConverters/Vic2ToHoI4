#include "OutSupplyZones.h"
#include "OutSupplyZone.h"
#include "OSCompatibilityLayer.h"



void HoI4::outputSupplyZones(const SupplyZones& supplyZones, const Configuration& theConfiguration)
{
	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/map/supplyareas"))
	{
		throw std::runtime_error(
			"Could not create \"output/" + theConfiguration.getOutputName() + "/map/supplyareas"
		);
	}

	for (const auto& zone: supplyZones.getSupplyZones())
	{
		if (auto possibleFileName = supplyZones.getSupplyZoneFileName(zone.first))
		{
			outputSupplyZone(zone.second, *possibleFileName, theConfiguration);
		}
	}
}
