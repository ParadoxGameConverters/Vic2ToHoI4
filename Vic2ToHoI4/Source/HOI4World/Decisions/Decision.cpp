#include "Decision.h"
#include "ParserHelpers.h"



HoI4::decision::decision(std::string decisionName, std::istream& theStream): name(std::move(decisionName))
{
	registerKeyword("icon", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString theIcon(theStream);
		icon = theIcon.getString();
	});
	registerKeyword("is_good", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString theIsGood(theStream);
		isGood = theIsGood.getString();
	});
	registerKeyword("allowed", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theAllowed(theStream);
		allowed = theAllowed.getString();
	});
	registerKeyword("highlight_states", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theHighlightStates(theStream);
		highlightStates = theHighlightStates.getString();
	});
	registerKeyword("available", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theAvailable(theStream);
		available = theAvailable.getString();
	});
	registerKeyword("days_mission_timeout", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt theTimeout(theStream);
		daysMissionTimeout = theTimeout.getInt();
	});
	registerKeyword("activation", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theActivation(theStream);
		activation = theActivation.getString();
	});
	registerKeyword("targets", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargets(theStream);
		targets = theTargets.getString();
	});
	registerKeyword("target_array", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem theTargetArray(theStream);
		targetArray = theTargetArray.getString();
	});
	registerKeyword("target_root_trigger", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargetRootTrigger(theStream);
		targetRootTrigger = theTargetRootTrigger.getString();
	});
	registerKeyword("target_trigger", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargetTrigger(theStream);
		targetTrigger = theTargetTrigger.getString();
	});
	registerKeyword("target_non_existing", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString yesString(theStream);
		targetNonExisting = yesString.getString() == "yes";
	});
	registerKeyword("visible", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theVisible(theStream);
		visible = theVisible.getString();
	});
	registerKeyword("cancel_trigger", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theCancelTrigger(theStream);
		cancelTrigger = theCancelTrigger.getString();
	});
	registerKeyword("targeted_modifier", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargetedModifier(theStream);
		targetedModifier = theTargetedModifier.getString();
	});
	registerKeyword("remove_trigger", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theRemoveTrigger(theStream);
		removeTrigger = theRemoveTrigger.getString();
	});
	registerKeyword("custom_cost_trigger", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theCustomCostTrigger(theStream);
		customCostTrigger = theCustomCostTrigger.getString();
	});
	registerKeyword("custom_cost_text", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem theCustomCostText(theStream);
		customCostText = theCustomCostText.getString();
	});
	registerKeyword("complete_effect", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theCompleteEffect(theStream);
		completeEffect = theCompleteEffect.getString();
	});
	registerKeyword("remove_effect", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theRemoveEffect(theStream);
		removeEffect = theRemoveEffect.getString();
	});
	registerKeyword("timeout_effect", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTimeoutEffect(theStream);
		timeoutEffect = theTimeoutEffect.getString();
	});
	registerKeyword("ai_will_do", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theAiWillDo(theStream);
		aiWillDo = theAiWillDo.getString();
	});
	registerKeyword("days_remove", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString theDaysRemove(theStream);
		daysRemove = theDaysRemove.getString();
	});
	registerKeyword("days_re_enable", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt theDaysReEnable(theStream);
		daysReEnable = theDaysReEnable.getInt();
	});
	registerKeyword("cost", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString theCost(theStream);
		cost = theCost.getString();
	});
	registerKeyword("fire_only_once", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString theFire(theStream);
		fireOnlyOnce = theFire.getString();
	});
	registerKeyword("modifier", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theModifier(theStream);
		modifier = theModifier.getString();
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


bool HoI4::decision::operator==(const decision& otherDecision) const
{
	return (name == otherDecision.name);
}