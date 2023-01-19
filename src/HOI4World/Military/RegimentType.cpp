#include "src/HOI4World/Military/RegimentType.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



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