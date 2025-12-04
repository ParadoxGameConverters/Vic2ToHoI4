#include "external/common_items/CommonRegexes.h"
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
	registerKeyword("allowed", [this](std::istream& theStream) {
		allowed = commonItems::stringOfItem(theStream).getString();
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
	registerKeyword("select_effect", [this](std::istream& theStream) {
		selectEffect = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("auto_complete", [this](std::istream& theStream) {
		autoComplete = commonItems::getString(theStream) == "yes";
	});
	registerKeyword("cancel", [this](std::istream& theStream) {
		cancel = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("complete_effect", [this](std::istream& theStream) {
		completeEffect = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("ai_will_do", [this](std::istream& theStream) {
		aiWillDo = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("is_manifest", [this](std::istream& theStream) {
		isManifest = commonItems::getString(theStream) == "yes";
	});
	registerKeyword("ratio_progress", [this](std::istream& theStream) {
		ratioProgress = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);
	clearRegisteredKeywords();
}

bool HoI4::FactionGoal::operator==(const FactionGoal& other) const
{
	return id == other.id && name == other.name && description == other.description && group == other.group &&
			 category == other.category && visible == other.visible && lockedGoal == other.lockedGoal &&
			 available == other.available && completed == other.completed && completeEffect == other.completeEffect;
}