#ifndef POLITICAL_DECISIONS_H
#define POLITICAL_DECISIONS_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Decisions/DecisionsInCategory.h"
#include "src/HOI4World/Decisions/IdeologicalDecisions.h"



namespace HoI4
{

class PoliticalDecisions: commonItems::parser
{
  public:
	void importDecisions(const std::string& filename);

	[[nodiscard]] const auto& getDecisions() const { return decisions; }

	void updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

  private:
	std::vector<IdeologicalDecisions> allIdeologicalDecisions;
	std::vector<DecisionsInCategory> decisions;
};

} // namespace HoI4



#endif // POLITICAL_DECISIONS_H