#ifndef HOI4_DECISIONS_H
#define HOI4_DECISIONS_H



#include "../../Configuration.h"
#include "../States/DefaultState.h"
#include "AgentRecruitmentDecisions.h"
#include "DecisionsCategories.h"
#include "DecisionsInCategory.h"
#include "ExiledGovernmentsDecisions.h"
#include "ForeignInfluenceDecisions.h"
#include "GenericDecisions.h"
#include "NavalTreatyDecisions.h"
#include "PoliticalDecisions.h"
#include "ResourceProspectingDecisions.h"
#include "StabilityWarSupportDecisions.h"
#include "newParser.h"
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

	void updateDecisions(const std::set<std::string>& majorIdeologies,
		 const std::map<int, int>& provinceToStateIdMap,
		 const std::map<int, DefaultState>& defaultStates,
		 const Events& theEvents);

	[[nodiscard]] const auto& getIdeologicalCategories() const { return *ideologicalCategories; }
	[[nodiscard]] const std::vector<DecisionsInCategory>& getAgentRecruitmentDecisions() const
	{
		return agentRecruitmentDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getStabilityDecisions() const
	{
		return stabilityDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getPoliticalDecisions() const
	{
		return politicalDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getExiledGovernmentsDecisions() const
	{
		return exiledGovernmentsDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getForeignInfluenceDecisions() const
	{
		return foreignInfluenceDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getNavalTreatyDecisions() const
	{
		return navalTreatyDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getResourceProspectingDecisions() const
	{
		return resourceProspectingDecisions.getDecisions();
	}
	[[nodiscard]] const std::vector<DecisionsInCategory>& getGenericDecisions() const
	{
		return genericDecisions.getDecisions();
	}

  private:
	void generateIdeologicalCategories(const std::set<std::string>& majorIdeologies);
	static std::string getIdeologicalIcon(const std::string& ideology);
	
	std::unique_ptr<DecisionsCategories> ideologicalCategories;

	AgentRecruitmentDecisions agentRecruitmentDecisions;
	StabilityWarSupportDecisions stabilityDecisions;
	PoliticalDecisions politicalDecisions;
	ExiledGovernmentsDecisions exiledGovernmentsDecisions;
	ForeignInfluenceDecisions foreignInfluenceDecisions;
	NavalTreatyDecisions navalTreatyDecisions;
	ResourceProspectingDecisions resourceProspectingDecisions;
	GenericDecisions genericDecisions;
};

} // namespace HoI4



#endif // HOI4_DECISIONS_H