#include "Idea.h"
#include "ParserHelpers.h"



HoI4::Idea::Idea(std::string ideaName, std::istream& theStream): name(std::move(ideaName))
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString nameString(theStream);
		altName = nameString.getString();
	});
	registerKeyword("ledger", [this](std::istream& theStream) {
		ledger = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("cost", [this](std::istream& theStream) {
		const commonItems::singleInt costString(theStream);
		cost = costString.getInt();
	});
	registerKeyword("removal_cost", [this](std::istream& theStream) {
		const commonItems::singleInt costString(theStream);
		removalCost = costString.getInt();
	});
	registerKeyword("level", [this](std::istream& theStream) {
		const commonItems::singleInt levelString(theStream);
		level = levelString.getInt();
	});
	registerKeyword("allowed", [this](std::istream& theStream) {
		const commonItems::stringOfItem allowedString(theStream);
		allowed = allowedString.getString();
	});
	registerKeyword("allowed_civil_war", [this](std::istream& theStream) {
		const commonItems::stringOfItem allowedString(theStream);
		allowedCivilWar = allowedString.getString();
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		visible = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("cancel", [this](std::istream& theStream) {
		const commonItems::stringOfItem cancelString(theStream);
		cancel = cancelString.getString();
	});
	registerKeyword("available", [this](std::istream& theStream) {
		const commonItems::stringOfItem availableString(theStream);
		available = availableString.getString();
	});
	registerKeyword("ai_will_do", [this](std::istream& theStream) {
		const commonItems::stringOfItem aiWillDoString(theStream);
		aiWillDo = aiWillDoString.getString();
	});
	registerKeyword("picture", [this](std::istream& theStream) {
		const commonItems::stringOfItem pictureString(theStream);
		picture = pictureString.getString();
	});
	registerKeyword("rule", [this](std::istream& theStream) {
		const commonItems::stringOfItem ruleString(theStream);
		rule = ruleString.getString();
	});
	registerKeyword("modifier", [this](std::istream& theStream) {
		const commonItems::stringOfItem modifierString(theStream);
		modifier = modifierString.getString();
	});
	registerKeyword("research_bonus", [this](std::istream& theStream) {
		const commonItems::stringOfItem researchBonusString(theStream);
		researchBonus = researchBonusString.getString();
	});
	registerKeyword("equipment_bonus", [this](std::istream& theStream) {
		const commonItems::stringOfItem bonusString(theStream);
		equipmentBonus = bonusString.getString();
	});
	registerKeyword("traits", [this](std::istream& theStream) {
		const commonItems::stringOfItem traitsString(theStream);
		traits = traitsString.getString();
	});
	registerKeyword("on_add", [this](std::istream& theStream) {
		const commonItems::stringOfItem onAddString(theStream);
		onAdd = onAddString.getString();
	});
	registerKeyword("allowed_to_remove", [this](std::istream& theStream) {
		const commonItems::stringOfItem allowedString(theStream);
		allowedToRemove = allowedString.getString();
	});
	registerKeyword("default", [this](std::istream& theStream) {
		const commonItems::singleString defaultString(theStream);
		isDefault = (defaultString.getString() == "yes");
	});
	registerKeyword("cancel_if_invalid", [this](std::istream& theStream) {
		const commonItems::singleString cancelIfInvalidString(theStream);
		cancelIfInvalid = (cancelIfInvalidString.getString() == "yes");
	});
	// no catch-all, as we want to emit errors if unhandled items are encountered

	parseStream(theStream);
	clearRegisteredKeywords();
}