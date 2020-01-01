#include "StateCategory.h"
#include "ParserHelpers.h"



HoI4::StateCategory::StateCategory(std::istream& theStream)
{
	registerKeyword(std::regex("local_building_slots"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt slotsInt(theStream);
		numberOfSlots = slotsInt.getInt();
	});
	registerKeyword(std::regex("[A-Za-z0-9\\_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}