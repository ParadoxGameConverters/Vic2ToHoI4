#include "src/HOI4World/States/StateCategory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::StateCategory::StateCategory(std::istream& theStream)
{
	registerKeyword("local_building_slots", [this](std::istream& theStream) {
		commonItems::singleInt slotsInt(theStream);
		numberOfSlots = slotsInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}