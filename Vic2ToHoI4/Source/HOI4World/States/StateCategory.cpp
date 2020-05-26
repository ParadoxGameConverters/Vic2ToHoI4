#include "StateCategory.h"
#include "ParserHelpers.h"



HoI4::StateCategory::StateCategory(std::istream& theStream)
{
	registerKeyword("local_building_slots", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt slotsInt(theStream);
		numberOfSlots = slotsInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}