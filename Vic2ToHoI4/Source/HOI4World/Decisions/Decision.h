#ifndef HOI4_DECISION_H
#define HOI4_DECISION_H


#include "Parser.h"
#include <optional>
#include <string>



namespace HoI4
{

class decision: commonItems::parser
{
  public:
	decision(std::string decisionName, std::istream& theStream);

	[[nodiscard]] std::string getName() const { return name; }
	[[nodiscard]] std::string getHighlightStateTargets() const { return highlightStateTargets; }
	[[nodiscard]] std::string getAvailable() const { return available; }
	[[nodiscard]] std::string getVisible() const { return visible; }
	[[nodiscard]] std::string getRemoveEffect() const { return removeEffect; }
	[[nodiscard]] std::string getTimeoutEffect() const { return timeoutEffect; }

	void setAllowed(const std::string& newAllowed) { allowed = newAllowed; }
	void setAvailable(const std::string& newAvailable) { available = newAvailable; }
	void setHighlightStateTargets(const std::string& newHighlightStates) { highlightStateTargets = newHighlightStates; }
	void setActivation(const std::string& newActivation) { activation = newActivation; }
	void setTargetTrigger(const std::string& newTargetTrigger) { targetTrigger = newTargetTrigger; }
	void setVisible(const std::string& newVisible) { visible = newVisible; }
	void setCompleteEffect(const std::string& newEffect) { completeEffect = newEffect; }
	void setTargetedModifier(const std::string& newTargetedModifier) { targetedModifier = newTargetedModifier; }
	void setRemoveEffect(const std::string& newEffect) { removeEffect = newEffect; }
	void setTimeoutEffect(const std::string& newEffect) { timeoutEffect = newEffect; }
	void setAiWillDo(const std::string& newAiWillDo) { aiWillDo = newAiWillDo; }
	void setModifier(const std::string& newModifier) { modifier = newModifier; }

	bool operator==(const decision& otherDecision) const;

	friend std::ostream& operator<<(std::ostream& outStream, const decision& outDecision);

  private:
	std::string name;
	std::string icon;
	std::string nameField;
	std::string isGood;
	std::string allowed;
	std::string highlightStateTargets;
	std::string available;
	std::optional<int> daysMissionTimeout;
	std::string activation;
	std::string targets;
	std::string targetArray;
	std::string targetRootTrigger;
	bool stateTarget = false;
	std::string targetTrigger;
	bool targetNonExisting = false;
	std::string removeTrigger;
	std::string customCostTrigger;
	std::string customCostText;
	std::string visible;
	std::string cancelTrigger;
	std::string onMapMode;
	std::string completeEffect;
	std::string targetedModifier;
	std::string removeEffect;
	std::string timeoutEffect;
	std::string aiWillDo;
	std::string fireOnlyOnce;
	std::optional<std::string> daysRemove;
	std::optional<int> daysReEnable;
	std::optional<std::string> cost;
	std::string modifier;
};

} // namespace HoI4



#endif // HOI4_DECISION_H