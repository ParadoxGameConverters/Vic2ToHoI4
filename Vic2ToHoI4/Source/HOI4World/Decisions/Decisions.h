#ifndef HOI4_DECISIONS_H
#define HOI4_DECISIONS_H


#include "newParser.h"
#include "IdeologicalDecisions.h"
#include "DecisionsCategory.h"
#include "ExiledGovernmentsDecisions.h"
#include "ForeignInfluenceDecisions.h"
#include "NavalTreatyDecisions.h"
#include "PoliticalDecisions.h"
#include "StabilityWarSupportDecisions.h"
#include "../../Configuration.h"
#include <map>
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
			return foreignInfluenceDecisions.getDecisions();
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getNavalTreatyDecisions() const
		{
			return navalTreatyDecisions.getDecisions();
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getGenericDecisions() const { return genericDecisions; }

	private:
		void updateGenericDecisions(
			const std::map<int, int>& provinceToStateIdMap,
			const std::set<std::string>& majorIdeologies
		);

		StabilityWarSupportDecisions stabilityDecisions;
		PoliticalDecisions politicalDecisions;
		ExiledGovernmentsDecisions exiledGovernmentsDecisions;
		ForeignInfluenceDecisions foreignInfluenceDecisions;
		NavalTreatyDecisions navalTreatyDecisions;
		std::vector<decisionsCategory> genericDecisions;
};

}




#endif // HOI4_DECISIONS_H