#ifndef HOI4_DECISIONS_CATEGORY_H
#define HOI4_DECISIONS_CATEGORY_H


#include "Decision.h"
#include "newParser.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Events;

class decisionsCategory: commonItems::parser
{
	public:
		decisionsCategory(std::string categoryName, std::istream& theStream);

		[[nodiscard]] std::vector<decision> getDecisions() const { return theDecisions; }
		[[nodiscard]] std::string getName() const { return name; }

		void replaceDecision(const decision& theDecision) {
			std::replace(theDecisions.begin(), theDecisions.end(), theDecision, theDecision);
		}
		void replaceDecisions(const std::vector<decision>& newDecisions) { theDecisions = newDecisions; }
		void addDecision(decision& theDecision) { theDecisions.push_back(theDecision); }

		void updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

		bool operator==(const decisionsCategory& otherCategory) const;

		friend std::ostream& operator<<(std::ostream& outStream, const decisionsCategory& outCategory);

	private:
		std::string name = "";
		std::vector<decision> theDecisions;

		void updateHoldTheIdeologyNationalReferendum(decision& decisionToUpdate, const Events& theEvents) const;
};

}



#endif // HOI4_DECISIONS_CATEGORY_H