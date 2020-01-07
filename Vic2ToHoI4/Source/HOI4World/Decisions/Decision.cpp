#include "Decision.h"
#include "ParserHelpers.h"



HoI4::decision::decision(std::string decisionName, std::istream& theStream):
	name(std::move(decisionName))
{
	registerKeyword(std::regex("icon"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString theIcon(theStream);
		icon = theIcon.getString();
	});
	registerKeyword(std::regex("is_good"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString theIsGood(theStream);
		isGood = theIsGood.getString();
	});
	registerKeyword(std::regex("allowed"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theAllowed(theStream);
		allowed = theAllowed.getString();
	});
	registerKeyword(std::regex("available"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theAvailable(theStream);
		available = theAvailable.getString();
	});
	registerKeyword(std::regex("days_mission_timeout"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleInt theTimeout(theStream);
		daysMissionTimeout = theTimeout.getInt();
	});
	registerKeyword(std::regex("activation"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theActivation(theStream);
		activation = theActivation.getString();
	});
	registerKeyword(std::regex("targets"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargets(theStream);
		targets = theTargets.getString();
	});
	registerKeyword(std::regex("target_array"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem theTargetArray(theStream);
		targetArray = theTargetArray.getString();
	});
	registerKeyword(std::regex("target_root_trigger"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargetRootTrigger(theStream);
		targetRootTrigger = theTargetRootTrigger.getString();
	});
	registerKeyword(std::regex("target_trigger"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theTargetTrigger(theStream);
		targetTrigger = theTargetTrigger.getString();
	});
	registerKeyword(std::regex("visible"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theVisible(theStream);
		visible = theVisible.getString();
	});
	registerKeyword(std::regex("cancel_trigger"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theCancelTrigger(theStream);
		cancelTrigger = theCancelTrigger.getString();
	});
	registerKeyword(std::regex("targeted_modifier"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theTargetedModifier(theStream);
		targetedModifier = theTargetedModifier.getString();
	});
	registerKeyword(std::regex("remove_trigger"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theRemoveTrigger(theStream);
		removeTrigger = theRemoveTrigger.getString();
	});
	registerKeyword(std::regex("custom_cost_trigger"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfObject theCustomCostTrigger(theStream);
		customCostTrigger = theCustomCostTrigger.getString();
	});
	registerKeyword(std::regex("custom_cost_text"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringOfItem theCustomCostText(theStream);
		customCostText = theCustomCostText.getString();
	});
	registerKeyword(std::regex("complete_effect"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theCompleteEffect(theStream);
		completeEffect = theCompleteEffect.getString();
	});
	registerKeyword(std::regex("remove_effect"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theRemoveEffect(theStream);
		removeEffect = theRemoveEffect.getString();
	});
	registerKeyword(std::regex("timeout_effect"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theTimeoutEffect(theStream);
		timeoutEffect = theTimeoutEffect.getString();
	});
	registerKeyword(std::regex("ai_will_do"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theAiWillDo(theStream);
		aiWillDo = theAiWillDo.getString();
	});
	registerKeyword(std::regex("days_remove"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleInt theDaysRemove(theStream);
		daysRemove = theDaysRemove.getInt();
	});
	registerKeyword(std::regex("days_re_enable"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleInt theDaysReEnable(theStream);
		daysReEnable = theDaysReEnable.getInt();
	});
	registerKeyword(std::regex("cost"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString theCost(theStream);
		cost = theCost.getString();
	});
	registerKeyword(std::regex("fire_only_once"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString theFire(theStream);
		fireOnlyOnce = theFire.getString();
	});
	registerKeyword(std::regex("modifier"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringOfObject theModifier(theStream);
		modifier = theModifier.getString();
	});

	parseStream(theStream);
}


bool HoI4::decision::operator==(const decision& otherDecision) const
{
	return (name == otherDecision.name);
}