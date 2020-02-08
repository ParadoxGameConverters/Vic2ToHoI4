#ifndef HOI4_DECISIONS_H
#define HOI4_DECISIONS_H



#include "newParser.h"
#include "DecisionsCategory.h"
#include "ExiledGovernmentsDecisions.h"
#include "ForeignInfluenceDecisions.h"
#include "GenericDecisions.h"
#include "NavalTreatyDecisions.h"
#include "PoliticalDecisions.h"
#include "StabilityWarSupportDecisions.h"
#include "../States/DefaultState.h"
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
			const std::map<int, DefaultState>& defaultStates,
			const Events& theEvents
		);

		[[nodiscard]] std::vector<decisionsCategory>& getStabilityDecisions()
		{
			return stabilityDecisions.getDecisions();
		}
		[[nodiscard]] const std::vector<decisionsCategory>& getPoliticalDecisions() const
		{
			return politicalDecisions.getDecisions();
		}
		[[nodiscard]] std::vector<decisionsCategory>& getExiledGovernmentsDecisions()
		{
			return exiledGovernmentsDecisions.getDecisions();
		}
		[[nodiscard]] std::vector<decisionsCategory>& getForeignInfluenceDecisions()
		{
			return foreignInfluenceDecisions.getDecisions();
		}
		[[nodiscard]] std::vector<decisionsCategory>& getNavalTreatyDecisions()
		{
			return navalTreatyDecisions.getDecisions();
		}
		[[nodiscard]] std::vector<decisionsCategory>& getResourceProspectingDecisions()
		{
			return resourceProspectingDecisions.getDecisions();
		}
		[[nodiscard]] std::vector<decisionsCategory>& getGenericDecisions()
		{
			return genericDecisions.getDecisions();
		}

	private:
		StabilityWarSupportDecisions stabilityDecisions;
		PoliticalDecisions politicalDecisions;
		ExiledGovernmentsDecisions exiledGovernmentsDecisions;
		ForeignInfluenceDecisions foreignInfluenceDecisions;
		NavalTreatyDecisions navalTreatyDecisions;
		DecisionsFile resourceProspectingDecisions;
		GenericDecisions genericDecisions;
};

}




#endif // HOI4_DECISIONS_H