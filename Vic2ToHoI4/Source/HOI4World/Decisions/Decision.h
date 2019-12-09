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
		decision(const std::string& decisionName, std::istream& theStream);

		std::string getName() const { return name; }
		std::string getTimeoutEffect() const { return timeoutEffect; }

		void setAvailable(const std::string& newAvailable) { available = newAvailable; }
		void setCompleteEffect(const std::string& newEffect) { completeEffect = newEffect; }
		void setTimeoutEffect(const std::string& newEffect) { timeoutEffect = newEffect; }
		void setModifier(const std::string& newModifier) { modifier = newModifier; }

		bool operator==(const HoI4::decision& otherDecision);

		friend std::ostream& operator<<(std::ostream& outStream, const decision& outDecision);

	private:
		std::string name;
		std::string icon;
		std::string isGood;
		std::string allowed;
		std::string available;
		std::optional<int> daysMissionTimeout;
		std::string activation;
		std::string targetTrigger;
		std::string removeTrigger;
		std::string visible;
		std::string cancelTrigger;
		std::string completeEffect;
		std::string removeEffect;
		std::string timeoutEffect;
		std::string aiWillDo;
		std::string fireOnlyOnce;
		std::optional<int> daysRemove;
		std::optional<int> daysReEnable;
		std::optional<int> cost;
		std::string modifier;
};

}




#endif // HOI4_DECISION_H