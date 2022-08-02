#include "src/HOI4World/Decisions/Decision.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"


HoI4::decision::decision(std::string decisionName)
{
	name = decisionName;
}

HoI4::decision::decision(std::string decisionName, std::istream& theStream): name(std::move(decisionName))
{
	registerKeyword("name", [this](std::istream& theStream) {
		const commonItems::singleString theName(theStream);
		nameField = theName.getString();
	});
	registerKeyword("icon", [this](std::istream& theStream) {
		const commonItems::singleString theIcon(theStream);
		icon = theIcon.getString();
	});
	registerKeyword("is_good", [this](std::istream& theStream) {
		const commonItems::singleString theIsGood(theStream);
		isGood = theIsGood.getString();
	});
	registerKeyword("allowed", [this](std::istream& theStream) {
		const commonItems::stringOfItem theAllowed(theStream);
		allowed = theAllowed.getString();
	});
	registerRegex("highlight_state_targets|highlight_states",
		 [this](const std::string& unused, std::istream& theStream) {
			 const commonItems::stringOfItem theHighlightStates(theStream);
			 highlightStateTargets = theHighlightStates.getString();
		 });
	registerKeyword("available", [this](std::istream& theStream) {
		const commonItems::stringOfItem theAvailable(theStream);
		available = theAvailable.getString();
	});
	registerKeyword("days_mission_timeout", [this](std::istream& theStream) {
		const commonItems::singleInt theTimeout(theStream);
		daysMissionTimeout = theTimeout.getInt();
	});
	registerKeyword("activation", [this](std::istream& theStream) {
		const commonItems::stringOfItem theActivation(theStream);
		activation = theActivation.getString();
	});
	registerKeyword("targets", [this](std::istream& theStream) {
		const commonItems::stringOfItem theTargets(theStream);
		targets = theTargets.getString();
	});
	registerKeyword("target_array", [this](std::istream& theStream) {
		const commonItems::stringOfItem theTargetArray(theStream);
		targetArray = theTargetArray.getString();
	});
	registerKeyword("target_root_trigger", [this](std::istream& theStream) {
		const commonItems::stringOfItem theTargetRootTrigger(theStream);
		targetRootTrigger = theTargetRootTrigger.getString();
	});
	registerKeyword("state_target", [this](std::istream& theStream) {
		const commonItems::singleString yesString(theStream);
		stateTarget = yesString.getString() == "yes";
	});
	registerKeyword("target_trigger", [this](std::istream& theStream) {
		const commonItems::stringOfItem theTargetTrigger(theStream);
		targetTrigger = theTargetTrigger.getString();
	});
	registerKeyword("target_non_existing", [this](std::istream& theStream) {
		const commonItems::singleString yesString(theStream);
		targetNonExisting = yesString.getString() == "yes";
	});
	registerKeyword("visible", [this](std::istream& theStream) {
		const commonItems::stringOfItem theVisible(theStream);
		visible = theVisible.getString();
	});
	registerKeyword("cancel_trigger", [this](std::istream& theStream) {
		const commonItems::stringOfItem theCancelTrigger(theStream);
		cancelTrigger = theCancelTrigger.getString();
	});
	registerKeyword("targeted_modifier", [this](std::istream& theStream) {
		const commonItems::stringOfItem theTargetedModifier(theStream);
		targetedModifier = theTargetedModifier.getString();
	});
	registerKeyword("remove_trigger", [this](std::istream& theStream) {
		const commonItems::stringOfItem theRemoveTrigger(theStream);
		removeTrigger = theRemoveTrigger.getString();
	});
	registerKeyword("custom_cost_trigger", [this](std::istream& theStream) {
		const commonItems::stringOfItem theCustomCostTrigger(theStream);
		customCostTrigger = theCustomCostTrigger.getString();
	});
	registerKeyword("custom_cost_text", [this](std::istream& theStream) {
		const commonItems::stringOfItem theCustomCostText(theStream);
		customCostText = theCustomCostText.getString();
	});
	registerKeyword("on_map_mode", [this](std::istream& theStream) {
		const commonItems::singleString theOnMapMode(theStream);
		onMapMode = theOnMapMode.getString();
	});
	registerKeyword("complete_effect", [this](std::istream& theStream) {
		const commonItems::stringOfItem theCompleteEffect(theStream);
		completeEffect = theCompleteEffect.getString();
	});
	registerKeyword("remove_effect", [this](std::istream& theStream) {
		const commonItems::stringOfItem theRemoveEffect(theStream);
		removeEffect = theRemoveEffect.getString();
	});
	registerKeyword("timeout_effect", [this](std::istream& theStream) {
		const commonItems::stringOfItem theTimeoutEffect(theStream);
		timeoutEffect = theTimeoutEffect.getString();
	});
	registerKeyword("ai_will_do", [this](std::istream& theStream) {
		const commonItems::stringOfItem theAiWillDo(theStream);
		aiWillDo = theAiWillDo.getString();
	});
	registerKeyword("days_remove", [this](std::istream& theStream) {
		const commonItems::singleString theDaysRemove(theStream);
		daysRemove = theDaysRemove.getString();
	});
	registerKeyword("days_re_enable", [this](std::istream& theStream) {
		const commonItems::singleInt theDaysReEnable(theStream);
		daysReEnable = theDaysReEnable.getInt();
	});
	registerKeyword("cost", [this](std::istream& theStream) {
		const commonItems::singleString theCost(theStream);
		cost = theCost.getString();
	});
	registerKeyword("fire_only_once", [this](std::istream& theStream) {
		const commonItems::singleString theFire(theStream);
		fireOnlyOnce = theFire.getString();
	});
	registerKeyword("modifier", [this](std::istream& theStream) {
		const commonItems::stringOfItem theModifier(theStream);
		modifier = theModifier.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


bool HoI4::decision::operator==(const decision& otherDecision) const
{
	return (name == otherDecision.name);
}