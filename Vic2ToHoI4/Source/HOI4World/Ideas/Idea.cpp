#include "Idea.h"
#include "ParserHelpers.h"



HoI4::Idea::Idea(const std::string& ideaName, std::istream& theStream):
	name(ideaName)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		altName = nameString.getString();
	});
	registerKeyword(std::regex("cost"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt costString(theStream);
		cost = costString.getInt();
	});
	registerKeyword(std::regex("removal_cost"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt costString(theStream);
		removalCost = costString.getInt();
	});
	registerKeyword(std::regex("level"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt levelString(theStream);
		level = levelString.getInt();
	});
	registerKeyword(std::regex("allowed"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem allowedString(theStream);
		allowed = allowedString.getString();
	});
	registerKeyword(std::regex("allowed_civil_war"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem allowedString(theStream);
		allowedCivilWar = allowedString.getString();
	});
	registerKeyword(std::regex("cancel"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem cancelString(theStream);
		cancel = cancelString.getString();
	});
	registerKeyword(std::regex("available"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem availableString(theStream);
		available = availableString.getString();
	});
	registerKeyword(std::regex("ai_will_do"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem aiWillDoString(theStream);
		aiWillDo = aiWillDoString.getString();
	});
	registerKeyword(std::regex("picture"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem pictureString(theStream);
		picture = pictureString.getString();
	});
	registerKeyword(std::regex("rule"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem ruleString(theStream);
		rule = ruleString.getString();
	});
	registerKeyword(std::regex("modifier"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem modifierString(theStream);
		modifier = modifierString.getString();
	});
	registerKeyword(std::regex("research_bonus"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem researchBonusString(theStream);
		researchBonus = researchBonusString.getString();
	});
	registerKeyword(std::regex("equipment_bonus"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem bonusString(theStream);
		equipmentBonus = bonusString.getString();
	});
	registerKeyword(std::regex("traits"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem traitsString(theStream);
		traits = traitsString.getString();
	});
	registerKeyword(std::regex("on_add"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem onAddString(theStream);
		onAdd = onAddString.getString();
	});
	registerKeyword(std::regex("allowed_to_remove"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem allowedString(theStream);
		allowedToRemove = allowedString.getString();
	});
	registerKeyword(std::regex("default"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString defaultString(theStream);
		isDefault = (defaultString.getString() == "yes");
	});
	registerKeyword(std::regex("cancel_if_invalid"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString cancelIfInvalidString(theStream);
		cancelIfInvalid = (cancelIfInvalidString.getString() == "yes");
	});

	parseStream(theStream);
}