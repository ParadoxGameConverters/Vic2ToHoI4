#include "MtgUnitMappings.h"
#include "MtgUnitMapping.h"



HoI4::MtgUnitMappings::MtgUnitMappings(std::istream& theStream)
{
	registerKeyword("link", [this](std::istream& theStream) {
		const MtgUnitMapping newMapping(theStream);
		unitMaps.insert(newMapping.getMapping());
	});

	parseStream(theStream);
}


bool HoI4::MtgUnitMappings::hasMatchingType(const std::string& Vic2Type) const
{
	return unitMaps.contains(Vic2Type);
}


std::vector<HoI4::HoI4UnitType> HoI4::MtgUnitMappings::getMatchingUnitInfo(const std::string& Vic2Type) const
{
	if (auto matchingUnit = unitMaps.find(Vic2Type); matchingUnit != unitMaps.end())
	{
		return matchingUnit->second;
	}
	else
	{
		return std::vector<HoI4UnitType>{};
	}
}