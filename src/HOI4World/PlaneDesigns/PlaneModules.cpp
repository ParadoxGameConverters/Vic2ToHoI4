#include "src/HOI4World/PlaneDesigns/PlaneModules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PlaneModules::PlaneModules(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& moduleSlot, std::istream& regexStream) {
		const commonItems::singleString module(regexStream);
		modules.insert(std::make_pair(moduleSlot, module.getString()));
	});

	parseStream(theStream);
}