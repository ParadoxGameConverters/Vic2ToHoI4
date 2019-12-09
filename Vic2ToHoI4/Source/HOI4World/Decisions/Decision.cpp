#include "Decision.h"
#include "ParserHelpers.h"



HoI4::decision::decision(const std::string& decisionName, std::istream& theStream):
	name(decisionName)
{
	registerKeyword(std::regex("icon"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString theIcon(theStream);
		icon = theIcon.getString();
	});
	registerKeyword(std::regex("is_good"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString theIsGood(theStream);
		isGood = theIsGood.getString();
	});
	registerKeyword(std::regex("allowed"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theAllowed(theStream);
		allowed = theAllowed.getString();
	});
	registerKeyword(std::regex("available"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theAvailable(theStream);
		available = theAvailable.getString();
	});
	registerKeyword(std::regex("days_mission_timeout"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt theTimeout(theStream);
		daysMissionTimeout = theTimeout.getInt();
	});
	registerKeyword(std::regex("activation"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theActivation(theStream);
		activation = theActivation.getString();
	});
	registerKeyword(std::regex("target_trigger"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theTargetTrigger(theStream);
		targetTrigger = theTargetTrigger.getString();
	});
	registerKeyword(std::regex("visible"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theVisible(theStream);
		visible = theVisible.getString();
	});
	registerKeyword(std::regex("cancel_trigger"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theCancelTrigger(theStream);
		cancelTrigger = theCancelTrigger.getString();
	});
	registerKeyword(std::regex("remove_trigger"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theRemoveTrigger(theStream);
		removeTrigger = theRemoveTrigger.getString();
	});
	registerKeyword(std::regex("complete_effect"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theCompleteEffect(theStream);
		completeEffect = theCompleteEffect.getString();
	});
	registerKeyword(std::regex("remove_effect"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theRemoveEffect(theStream);
		removeEffect = theRemoveEffect.getString();
	});
	registerKeyword(std::regex("timeout_effect"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theTimeoutEffect(theStream);
		timeoutEffect = theTimeoutEffect.getString();
	});
	registerKeyword(std::regex("ai_will_do"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject theAiWillDo(theStream);
		aiWillDo = theAiWillDo.getString();
	});
	registerKeyword(std::regex("days_remove"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt theDaysRemove(theStream);
		daysRemove = theDaysRemove.getInt();
	});
	registerKeyword(std::regex("days_re_enable"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt theDaysReEnable(theStream);
		daysReEnable = theDaysReEnable.getInt();
	});
	registerKeyword(std::regex("cost"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt theCost(theStream);
		cost = theCost.getInt();
	});
	registerKeyword(std::regex("fire_only_once"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString theFire(theStream);
		fireOnlyOnce = theFire.getString();
	});
	registerKeyword(std::regex("modifier"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfObject themodifier(theStream);
		modifier = themodifier.getString();
	});

	parseStream(theStream);
}


bool HoI4::decision::operator==(const HoI4::decision& otherDecision)
{
	return (name == otherDecision.name);
}