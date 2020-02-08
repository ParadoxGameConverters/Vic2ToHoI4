#include "Decisions.h"
#include "ResourceProspectingDecisionsUpdater.h"
#include "../Events/Events.h"
#include <regex>



HoI4::decisions::decisions(const Configuration& theConfiguration)
{
	stabilityDecisions.importDecisions(theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt");
	politicalDecisions.importDecisions("ideologicalDecisions.txt");
	exiledGovernmentsDecisions.importDecisions(
		theConfiguration.getHoI4Path() + "/common/decisions/_exiled_governments_decisions.txt"
	);
	foreignInfluenceDecisions.importDecisions(
		theConfiguration.getHoI4Path() + "/common/decisions/foreign_influence.txt"
	);
	foreignInfluenceDecisions.importDecisions("DataFiles/foreignInfluenceDecisions.txt");
	navalTreatyDecisions.importDecisions(theConfiguration.getHoI4Path() + "/common/decisions/MTG_naval_treaty.txt");
	resourceProspectingDecisions.importDecisions(
		theConfiguration.getHoI4Path() + "/common/decisions/resource_prospecting.txt"
	);
	genericDecisions.importDecisions(theConfiguration.getHoI4Path() + "/common/decisions/_generic_decisions.txt");
}


void HoI4::decisions::updateDecisions(
	const std::set<std::string>& majorIdeologies,
	const std::map<int, int>& provinceToStateIdMap,
	const std::map<int, DefaultState>& defaultStates,
	const Events& theEvents
)
{
	stabilityDecisions.updateDecisions(majorIdeologies);
	politicalDecisions.updateDecisions(majorIdeologies, theEvents);
	exiledGovernmentsDecisions.updateDecisions(majorIdeologies);
	foreignInfluenceDecisions.updateDecisions(majorIdeologies);
	navalTreatyDecisions.updateDecisions(majorIdeologies);
	updateResourceProspectingDecisions(resourceProspectingDecisions, provinceToStateIdMap, defaultStates);
	genericDecisions.updateDecisions(provinceToStateIdMap, majorIdeologies);
}