#include "UnitMapping.h"
#include "ParserHelpers.h"



HoI4::UnitMapping::UnitMapping(std::istream& theStream)
{
	registerKeyword("vic", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString typeString(theStream);
		Vic2Type = typeString.getString();
	});
	registerKeyword("hoi", [this](const std::string& unused, std::istream& theStream) {
		const HoI4UnitType theUnit(theStream);
		HoI4Types.push_back(theUnit);
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


std::optional<std::pair<std::string, std::vector<HoI4::HoI4UnitType>>> HoI4::UnitMapping::getMappings() const
{
	if (Vic2Type)
	{
		return std::make_pair(*Vic2Type, HoI4Types);
	}
	else
	{
		return std::nullopt;
	}
}