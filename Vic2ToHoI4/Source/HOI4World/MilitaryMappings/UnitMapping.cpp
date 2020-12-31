#include "UnitMapping.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::UnitMapping::UnitMapping(std::istream& theStream)
{
	registerKeyword("vic", [this](std::istream& theStream) {
		const commonItems::singleString typeString(theStream);
		Vic2Type = typeString.getString();
	});
	registerKeyword("hoi", [this](std::istream& theStream) {
		const HoI4UnitType theUnit(theStream);
		HoI4Types.push_back(theUnit);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

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