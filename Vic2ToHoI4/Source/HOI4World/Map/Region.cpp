#include "Region.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Region::Region(std::istream& theStream)
{
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt idString(theStream);
		ID = idString.getInt();
	});
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("provinces", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList provinceNumbers(theStream);
		provinces = provinceNumbers.getInts();
	});
	registerKeyword("static_modifiers", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::assignments staticModifierStrings(theStream);
		staticModifiers = staticModifierStrings.getAssignments();
	});
	registerKeyword("naval_terrain", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString terrainString(theStream);
		navalTerrain = terrainString.getString();
	});
	registerKeyword("weather", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem weatherString(theStream);
		weather = weatherString.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}