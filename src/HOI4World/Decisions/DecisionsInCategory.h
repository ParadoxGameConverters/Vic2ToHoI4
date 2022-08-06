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
	explicit DecisionsInCategory(std::string category_name): name(std::move(category_name)) {}
	DecisionsInCategory(std::string categoryName, std::istream& theStream);
	
	[[nodiscard]] auto getDecisions() const { return theDecisions; }
	[[nodiscard]] std::map<std::string, std::string> getLocalisation() const { return localisation; }
	[[nodiscard]] const auto& getcustomLocalisation() const { return customLocalisation; }
	[[nodiscard]] const auto& getName() const { return name; }

	void addCustomLocalisation(const std::pair<std::string, std::string>& newLoc) { customLocalisation.emplace(newLoc); }
	void addDecision(decision& theDecision) { theDecisions.push_back(theDecision); }
	void addLocalisation(const std::pair<std::string, std::string>& newLoc) { localisation.emplace(newLoc); }

	void replaceDecision(const decision& theDecision)
	{
		std::replace(theDecisions.begin(), theDecisions.end(), theDecision, theDecision);
	}
	void replaceDecisions(const std::vector<decision>& newDecisions) { theDecisions = newDecisions; }

	void updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

	bool operator==(const DecisionsInCategory& otherCategory) const;

	friend std::ostream& operator<<(std::ostream& outStream, const DecisionsInCategory& outCategory);

  private:
	std::string name = "";
	std::vector<decision> theDecisions;
	std::map<std::string, std::string> localisation;
	std::map<std::string, std::string> customLocalisation;

	void updateHoldTheIdeologyNationalReferendum(decision& decisionToUpdate, const Events& theEvents) const;
};

} // namespace HoI4



#endif // HOI4_DECISIONS_IN_CATEGORY_H