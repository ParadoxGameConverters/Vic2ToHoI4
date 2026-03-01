#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Parser.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Factions/FactionRules.h"



HoI4::FactionRule::FactionRule(const std::string& id, std::istream& theStream): id(std::move(id))
{
	registerKeyword("type", [this](std::istream& theStream) {
		type = commonItems::getString(theStream);
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		visible = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("available", [this](std::istream& theStream) {
		available = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("can_remove", [this](std::istream& theStream) {
		canRemove = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("trigger", [this](std::istream& theStream) {
		trigger = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("dismiss_member_trigger", [this](std::istream& theStream) {
		dismissMemberTrigger = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("government_in_exile_allowed_trigger", [this](std::istream& theStream) {
		governmentInExileAllowedTrigger = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("peace_action_modifiers", [this](std::istream& theStream) {
		peaceActionModifiers = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("modifier", [this](std::istream& theStream) {
		modifier = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("effect", [this](std::istream& theStream) {
		effect = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("ai_will_do", [this](std::istream& theStream) {
		aiWillDo = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
	parseStream(theStream);
	clearRegisteredKeywords();
}

bool HoI4::FactionRule::operator==(const FactionRule& other) const
{
	return id == other.id && type == other.type && visible == other.visible && available == other.available &&
			 canRemove == other.canRemove && trigger == other.trigger &&
			 dismissMemberTrigger == other.dismissMemberTrigger &&
			 governmentInExileAllowedTrigger == other.governmentInExileAllowedTrigger &&
			 peaceActionModifiers == other.peaceActionModifiers && modifier == other.modifier && effect == other.effect &&
			 aiWillDo == other.aiWillDo;
}