#include "RegimentType.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::RegimentType::RegimentType(const std::string& _type, std::istream& theStream): type(_type)
{
	registerKeyword("x", [this](std::istream& theStream) {
		const commonItems::singleInt xInt(theStream);
		x = xInt.getInt();
	});
	registerKeyword("y", [this](std::istream& theStream) {
		const commonItems::singleInt yInt(theStream);
		y = yInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}