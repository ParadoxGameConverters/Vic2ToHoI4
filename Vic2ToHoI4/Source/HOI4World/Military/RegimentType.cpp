#include "RegimentType.h"
#include "ParserHelpers.h"



HoI4::RegimentType::RegimentType(const std::string& _type, std::istream& theStream): type(_type)
{
	registerKeyword("x", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt xInt(theStream);
		x = xInt.getInt();
	});
	registerKeyword("y", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt yInt(theStream);
		y = yInt.getInt();
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}