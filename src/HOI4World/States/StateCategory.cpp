#include "StateCategory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::StateCategory::StateCategory(std::istream& theStream)
{
	registerKeyword("local_building_slots", [this](std::istream& theStream) {
		commonItems::singleInt slotsInt(theStream);
		numberOfSlots = slotsInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}