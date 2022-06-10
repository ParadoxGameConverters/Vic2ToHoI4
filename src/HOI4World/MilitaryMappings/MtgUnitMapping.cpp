#include "src/HOI4World/MilitaryMappings/MtgUnitMapping.h"
#include "external/common_items/ParserHelpers.h"



HoI4::MtgUnitMapping::MtgUnitMapping(std::istream& theStream)
{
	registerKeyword("vic", [this](std::istream& theStream) {
		const commonItems::singleString typeString(theStream);
		Vic2Type = typeString.getString();
	});
	registerKeyword("hoi", [this](std::istream& theStream) {
		const HoI4UnitType theUnit(theStream);
		HoI4Types.push_back(theUnit);
	});

	parseStream(theStream);
}