#include "MtgUnitMapping.h"
#include "ParserHelpers.h"



HoI4::MtgUnitMapping::MtgUnitMapping(std::istream& theStream)
{
	registerKeyword(std::regex("vic"), [this](const std::string & unused, std::istream & theStream)
	{
		const commonItems::singleString typeString(theStream);
		Vic2Type = typeString.getString();
	});
	registerKeyword(std::regex("hoi"), [this](const std::string & unused, std::istream & theStream)
	{
		const HoI4UnitType theUnit(theStream);
		HoI4Types.push_back(theUnit);
	});

	parseStream(theStream);
}