#include "src/HOI4World/States/StateCategory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::StateCategory::StateCategory(std::string name, std::istream& theStream): name_(std::move(name))
{
	registerKeyword("local_building_slots", [this](std::istream& theStream) {
		commonItems::singleInt slotsInt(theStream);
		numberOfSlots = slotsInt.getInt();
	});
	registerKeyword("buildings_max_level", [this](std::istream& theStream) {
		for (const auto& [building, levelStr]: commonItems::assignments(theStream).getAssignments())
		{
			buildingsMaxLevels.emplace(building, std::stoi(levelStr));
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}


int HoI4::StateCategory::getBuildingMaxLevel(const std::string& building) const
{
	int maxLevel = 10;

	if (buildingsMaxLevels.contains(building))
	{
		maxLevel = buildingsMaxLevels.at(building);
	}

	return maxLevel;
}