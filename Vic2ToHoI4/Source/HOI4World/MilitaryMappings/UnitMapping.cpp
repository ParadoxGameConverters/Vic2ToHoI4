#include "UnitMapping.h"
#include "ParserHelpers.h"



HoI4::UnitMapping::UnitMapping(std::istream& theStream)
{
	registerKeyword(std::regex("vic"), [this](const std::string & unused, std::istream& theStream)
	{
		const commonItems::singleString typeString(theStream);
		Vic2Type = typeString.getString();
	});
	registerKeyword(std::regex("hoi"), [this](const std::string & unused, std::istream& theStream)
	{
		HoI4UnitType theUnit(theStream);
		HoI4Type = theUnit;
	});

	parseStream(theStream);
}


std::optional<std::pair<std::string, std::optional<HoI4::HoI4UnitType>>> HoI4::UnitMapping::getMappings() const
{
	if (Vic2Type)
	{
		return std::make_pair(*Vic2Type, HoI4Type);
	}
	else
	{
		return std::nullopt;
	}
}