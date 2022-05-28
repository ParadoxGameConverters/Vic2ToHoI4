#include "RegimentTypeGroup.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::RegimentTypeGroup::RegimentTypeGroup(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		const RegimentType regimentType(name, theStream);
		regimentTypes.push_back(regimentType);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}