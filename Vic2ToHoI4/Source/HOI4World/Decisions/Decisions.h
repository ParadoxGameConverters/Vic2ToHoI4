#ifndef HOI4_DECISIONS_H
#define HOI4_DECISIONS_H


#include "newParser.h"
#include "IdeologicalDecisions.h"
#include "DecisionsCategories.h"
#include "DecisionsCategory.h"
#include <memory>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Events;


class decisions: commonItems::parser
{
	public:
		decisions() noexcept;

		void updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

		[[nodiscard]] const DecisionsCategories& getDecisionsCategories() const { return *decisionsCategories; }
		[[nodiscard]] const std::vector<decisionsCategory>& getStabilityDecisions() const { return stabilityDecisions; }
		[[nodiscard]] const std::vector<decisionsCategory>& getPoliticalDecisions() const { return politicalDecisions; }

	private:
		void updateStabilityDecisions(const std::set<std::string>& majorIdeologies);
		void updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents);

		std::unique_ptr<DecisionsCategories> decisionsCategories;

		std::vector<decisionsCategory> stabilityDecisions;
		std::vector<decisionsCategory> politicalDecisions;

		std::vector<IdeologicalDecisions> allIdeologicalDecisions;
};

}




#endif // HOI4_DECISIONS_H