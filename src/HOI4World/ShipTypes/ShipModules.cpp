#include "src/HOI4World/ShipTypes/ShipModules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::shipModules::shipModules(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& moduleSlot, std::istream& theStream) {
		const commonItems::singleString module(theStream);
		modules.insert(std::make_pair(moduleSlot, module.getString()));
	});

	parseStream(theStream);
}