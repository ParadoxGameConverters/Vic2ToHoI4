#include "OperationFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Operation::Factory::Factory()
{
	registerKeyword("icon", [this](std::istream& theStream) {
		operation->icon = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("priority", [this](std::istream& theStream) {
		operation->priority = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("prevent_captured_operative_to_die", [this](const std::string& unused, std::istream& theStream) {
		commonItems::ignoreItem(unused, theStream);
		operation->preventCapturedOperativeToDie = true;
	});
	registerKeyword("days", [this](std::istream& theStream) {
		operation->days = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("network_strength", [this](std::istream& theStream) {
		operation->networkStrength = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("operatives", [this](std::istream& theStream) {
		operation->operatives = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		operation->visible = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("scale_cost_independent_of_target", [this](const std::string& unused, std::istream& theStream) {
		commonItems::ignoreItem(unused, theStream);
		operation->scaleCostIndependentOfTarget = true;
	});
	registerKeyword("requirements", [this](std::istream& theStream) {
		operation->requirements = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("selection_target_state", [this](std::istream& theStream) {
		operation->selectionTargetState = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("selection_target", [this](std::istream& theStream) {
		operation->selectionTarget = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("allowed", [this](std::istream& theStream) {
		operation->allowed = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("available", [this](std::istream& theStream) {
		operation->available = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("awarded_tokens", [this](std::istream& theStream) {
		operation->awardedTokens = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("equipment", [this](std::istream& theStream) {
		operation->equipment = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("on_start", [this](std::istream& theStream) {
		operation->onStart = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("required_tokens", [this](std::istream& theStream) {
		operation->requiredTokens = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("will_lead_to_war_with", [this](const std::string& unused, std::istream& theStream) {
		commonItems::ignoreItem(unused, theStream);
		operation->willLeadToWarWith = true;
	});
	registerKeyword("risk_chance", [this](std::istream& theStream) {
		operation->riskChance = static_cast<float>(commonItems::singleDouble{theStream}.getDouble());
	});
	registerKeyword("outcome_extra_chance", [this](std::istream& theStream) {
		operation->outcomeExtraChance = static_cast<float>(commonItems::singleDouble{theStream}.getDouble());
	});
	registerKeyword("risk_modifiers", [this](std::istream& theStream) {
		operation->riskModifiers = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("outcome_modifiers", [this](std::istream& theStream) {
		operation->outcomeModifiers = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("cost_modifiers", [this](std::istream& theStream) {
		operation->costModifiers = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("experience", [this](std::istream& theStream) {
		operation->experience = static_cast<float>(commonItems::singleDouble{theStream}.getDouble());
	});
	registerKeyword("cost_multiplier", [this](std::istream& theStream) {
		operation->costMultiplier = static_cast<float>(commonItems::singleDouble{theStream}.getDouble());
	});
	registerKeyword("outcome_execute", [this](std::istream& theStream) {
		operation->outcomeExecute = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("outcome_extra_execute", [this](std::istream& theStream) {
		operation->outcomeExtraExecute = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("outcome_potential", [this](std::istream& theStream) {
		operation->outcomePotential = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("target_weight", [this](std::istream& theStream) {
		operation->targetWeight = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("phases", [this](std::istream& theStream) {
		operation->phases.push_back(commonItems::stringOfItem{theStream}.getString());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<HoI4::Operation> HoI4::Operation::Factory::getOperation(std::string name, std::istream& theStream)
{
	operation = std::make_unique<Operation>();
	operation->name = std::move(name);

	parseStream(theStream);
	return std::move(operation);
}
