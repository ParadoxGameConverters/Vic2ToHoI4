#include "RegimentTypeGroup.h"



HoI4::RegimentTypeGroup::RegimentTypeGroup(std::istream& theStream)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& name, std::istream& theStream) {
		const RegimentType regimentType(name, theStream);
		regimentTypes.push_back(regimentType);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}