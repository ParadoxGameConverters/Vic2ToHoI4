#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Factions/FactionGoals.h"



HoI4::FactionGoal::FactionGoal(const std::string& id, std::istream& theStream): id(std::move(id))
{
	registerKeyword("name", [this](std::istream& theStream) {
		name = commonItems::getString(theStream);
	});
	registerKeyword("description", [this](std::istream& theStream) {
		description = commonItems::getString(theStream);
	});
	registerKeyword("group", [this](std::istream& theStream) {
		group = commonItems::getString(theStream);
	});
	registerKeyword("category", [this](std::istream& theStream) {
		category = commonItems::getString(theStream);
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		visible = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("locked_goal", [this](std::istream& theStream) {
		lockedGoal = commonItems::getString(theStream) == "yes";
	});
	registerKeyword("available", [this](std::istream& theStream) {
		available = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("completed", [this](std::istream& theStream) {
		completed = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("complete_effect", [this](std::istream& theStream) {
		completeEffect = commonItems::stringOfItem(theStream).getString();
	});
	parseStream(theStream);
	clearRegisteredKeywords();
}