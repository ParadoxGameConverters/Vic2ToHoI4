#ifndef HOI4_DECISIONS_IN_CATEGORY_H
#define HOI4_DECISIONS_IN_CATEGORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Decisions/Decision.h"
#include "src/HOI4World/Events/Events.h"
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class DecisionsInCategory: commonItems::parser
{
  public:
	DecisionsInCategory(std::string categoryName, std::istream& theStream);

	[[nodiscard]] auto getDecisions() const { return theDecisions; }
	[[nodiscard]] const auto& getName() const { return name; }

	void replaceDecision(const decision& theDecision)
	{
		std::replace(theDecisions.begin(), theDecisions.end(), theDecision, theDecision);
	}
	void replaceDecisions(const std::vector<decision>& newDecisions) { theDecisions = newDecisions; }
	void addDecision(decision& theDecision) { theDecisions.push_back(theDecision); }

	void updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

	bool operator==(const DecisionsInCategory& otherCategory) const;

	friend std::ostream& operator<<(std::ostream& outStream, const DecisionsInCategory& outCategory);

  private:
	std::string name = "";
	std::vector<decision> theDecisions;

	void updateHoldTheIdeologyNationalReferendum(decision& decisionToUpdate, const Events& theEvents) const;
};

} // namespace HoI4



#endif // HOI4_DECISIONS_IN_CATEGORY_H