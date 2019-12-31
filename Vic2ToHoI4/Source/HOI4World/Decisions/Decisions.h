#ifndef HOI4_DECISIONS_H
#define HOI4_DECISIONS_H


#include "newParser.h"
#include "IdeologicalDecisions.h"
#include "DecisionsCategories.h"
#include "DecisionsCategory.h"
#include "ExiledGovernmentsDecisions.h"
#include "PoliticalDecisions.h"
#include "StabilityWarSupportDecisions.h"
#include "../../Configuration.h"
#include <map>
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
		explicit decisions(const Configuration& theConfiguration);

		void updateDecisions(
			const std::set<std::string>& majorIdeologies,
			const std::map<int, int>& provinceToStateIdMap,
			const Events& theEvents
		);

		[[nodiscard]] const DecisionsCategories& getDecisionsCategories() const { return *decisionsCategories; }
		[[nodiscard]] const std::vector<decisionsCategory>& getStabilityDecisions() const
		{
			return stabilityDecisions.getDecisions();
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getPoliticalDecisions() const
		{
			return politicalDecisions.getDecisions();
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getExiledGovernmentsDecisions() const
		{
			return exiledGovernmentsDecisions.getDecisions();
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getForeignInfluenceDecisions() const
		{
			return foreignInfluenceDecisions;
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getMtgNavalTreatyDecisions() const
		{
			return mtgNavalTreatyDecisions;
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getGenericDecisions() const { return genericDecisions; }

	private:
		void updateForeignInfluenceDecisions(const std::set<std::string>& majorIdeologies);
		void updateMtgNavalTreatyDecisions(const std::set<std::string>& majorIdeologies);
		void updateGenericDecisions(
			const std::map<int, int>& provinceToStateIdMap,
			const std::set<std::string>& majorIdeologies
		);

		std::unique_ptr<DecisionsCategories> decisionsCategories;

		StabilityWarSupportDecisions stabilityDecisions;
		PoliticalDecisions politicalDecisions;
		ExiledGovernmentsDecisions exiledGovernmentsDecisions;
		std::vector<decisionsCategory> foreignInfluenceDecisions;
		std::vector<decisionsCategory> mtgNavalTreatyDecisions;
		std::vector<decisionsCategory> genericDecisions;
};

}




#endif // HOI4_DECISIONS_H