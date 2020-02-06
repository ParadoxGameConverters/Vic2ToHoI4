#ifndef HOI4_DECISION_H
#define HOI4_DECISION_H


#include "newParser.h"
#include <optional>
#include <string>



namespace HoI4
{

class decision: commonItems::parser
{
	public:
		decision(std::string decisionName, std::istream& theStream);

		[[nodiscard]] std::string getName() const { return name; }
		[[nodiscard]] std::string getVisible() const { return visible; }
		[[nodiscard]] std::string getTimeoutEffect() const { return timeoutEffect; }

		void setAvailable(const std::string& newAvailable) { available = newAvailable; }
		void setHighlightStates(const std::string& newHighlightStates) { highlightStates = newHighlightStates; }
		void setTargetTrigger(const std::string& newTargetTrigger) { targetTrigger = newTargetTrigger; }
		void setVisible(const std::string& newVisible) { visible = newVisible; }
		void setCompleteEffect(const std::string& newEffect) { completeEffect = newEffect; }
		void setRemoveEffect(const std::string& newEffect) { removeEffect = newEffect; }
		void setTimeoutEffect(const std::string& newEffect) { timeoutEffect = newEffect; }
		void setTargetedModifier(const std::string& newTargetedModifier) { targetedModifier = newTargetedModifier; }
		void setAiWillDo(const std::string& newAiWillDo) { aiWillDo = newAiWillDo; }
		void setModifier(const std::string& newModifier) { modifier = newModifier; }

		bool operator==(const decision& otherDecision) const;

		friend std::ostream& operator<<(std::ostream& outStream, const decision& outDecision);

	private:
		std::string name;
		std::string icon;
		std::string isGood;
		std::string allowed;
		std::string highlightStates;
		std::string available;
		std::optional<int> daysMissionTimeout;
		std::string activation;
		std::string targets;
		std::string targetArray;
		std::string targetRootTrigger;
		std::string targetTrigger;
		std::string removeTrigger;
		std::string customCostTrigger;
		std::string customCostText;
		std::string visible;
		std::string cancelTrigger;
		std::string completeEffect;
		std::string targetedModifier;
		std::string removeEffect;
		std::string timeoutEffect;
		std::string aiWillDo;
		std::string fireOnlyOnce;
		std::optional<int> daysRemove;
		std::optional<int> daysReEnable;
		std::optional<std::string> cost;
		std::string modifier;
};

}




#endif // HOI4_DECISION_H