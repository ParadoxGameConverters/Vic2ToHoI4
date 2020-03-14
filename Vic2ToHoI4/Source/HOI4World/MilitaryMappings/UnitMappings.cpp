#include "UnitMappings.h"
#include "ParserHelpers.h"
#include "UnitMapping.h"


HoI4::UnitMappings::UnitMappings(std::istream& theStream)
{
	registerKeyword("link", [this](const std::string& unused, std::istream& theStream) {
		const UnitMapping newMapping(theStream);
		if (auto mapping = newMapping.getMappings(); mapping)
		{
			unitMap.insert(*mapping);
		}
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


bool HoI4::UnitMappings::hasMatchingType(const std::string& Vic2Type) const
{
	return unitMap.count(Vic2Type) > 0;
}


std::vector<HoI4::HoI4UnitType> HoI4::UnitMappings::getMatchingUnitInfo(const std::string& Vic2Type) const
{
	if (const auto& matchingUnit = unitMap.find(Vic2Type); matchingUnit != unitMap.end())
	{
		return matchingUnit->second;
	}
	else
	{
		return std::vector<HoI4::HoI4UnitType>{};
	}
}