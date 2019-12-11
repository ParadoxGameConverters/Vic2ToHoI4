#include "UnitMappings.h"
#include "UnitMapping.h"



HoI4::UnitMappings::UnitMappings(std::istream& theStream)
{
	registerKeyword(std::regex("link"), [this](const std::string & unused, std::istream & theStream)
	{
		const UnitMapping newMapping(theStream);
		if (auto mapping = newMapping.getMappings(); mapping)
		{
			unitMap.insert(*mapping);
		}
	});

	parseStream(theStream);
}


bool HoI4::UnitMappings::hasMatchingType(const std::string& Vic2Type) const
{
	return unitMap.count(Vic2Type) > 0;
}


std::optional<HoI4::HoI4UnitType> HoI4::UnitMappings::getMatchingUnitInfo(const std::string& Vic2Type) const
{
	if (hasMatchingType(Vic2Type))
	{
		return unitMap.find(Vic2Type)->second;
	}
	else
	{
		return std::nullopt;
	}
}