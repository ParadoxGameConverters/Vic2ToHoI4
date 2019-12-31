#include "Decisions.h"
#include "Decision.h"
#include "../Events.h"
#include <sstream>
#include <regex>



HoI4::decisions::decisions(const Configuration& theConfiguration)
{
	std::ifstream stabilityWarSupportFile(
		theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt"
	);
	if (!stabilityWarSupportFile.is_open())
	{
		throw std::runtime_error(
			"Could not open " + theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt"
		);
	}
	stabilityDecisions.importDecisions(stabilityWarSupportFile);
	stabilityWarSupportFile.close();

	std::ifstream ideologicalDecisionsFile("ideologicalDecisions.txt");
	if (!ideologicalDecisionsFile.is_open())
	{
		throw std::runtime_error("Could not open ideologicalDecisions.txt");
	}
	politicalDecisions.importDecisions(ideologicalDecisionsFile);
	ideologicalDecisionsFile.close();

	std::ifstream exiledGovernmentsFile(
		theConfiguration.getHoI4Path() + "/common/decisions/_exiled_governments_decisions.txt"
	);
	if (!exiledGovernmentsFile.is_open())
	{
		throw std::runtime_error(
			"Could not open " + theConfiguration.getHoI4Path() + "/common/decisions/_exiled_governments_decisions.txt"
		);
	}
	exiledGovernmentsDecisions.importDecisions(exiledGovernmentsFile);
	exiledGovernmentsFile.close();

	std::ifstream foreignInfluenceFile(
		theConfiguration.getHoI4Path() + "/common/decisions/foreign_influence.txt"
	);
	if (!foreignInfluenceFile.is_open())
	{
		throw std::runtime_error(
			"Could not open " + theConfiguration.getHoI4Path() + "/common/decisions/foreign_influence.txt"
		);
	}
	foreignInfluenceDecisions.importDecisions(foreignInfluenceFile);
	foreignInfluenceFile.close();
	foreignInfluenceFile.open("DataFiles/foreignInfluenceDecisions.txt");
	if (!foreignInfluenceFile.is_open())
	{
		throw std::runtime_error("Could not open DataFiles/foreignInfluenceDecisions.txt");
	}
	foreignInfluenceDecisions.importDecisions(foreignInfluenceFile);
	foreignInfluenceFile.close();

	std::ifstream navalTreatyFile(
		theConfiguration.getHoI4Path() + "/common/decisions/MTG_naval_treaty.txt"
	);
	if (!navalTreatyFile.is_open())
	{
		throw std::runtime_error(
			"Could not open " + theConfiguration.getHoI4Path() + "/common/decisions/MTG_naval_treaty.txt"
		);
	}
	navalTreatyDecisions.importDecisions(navalTreatyFile);
	navalTreatyFile.close();

	std::ifstream genericDecisionsFile(
		theConfiguration.getHoI4Path() + "/common/decisions/_generic_decisions.txt"
	);
	if (!genericDecisionsFile.is_open())
	{
		throw std::runtime_error(
			"Could not open " + theConfiguration.getHoI4Path() + "/common/decisions/_generic_decisions.txt"
		);
	}
	genericDecisions.importDecisions(genericDecisionsFile);
	genericDecisionsFile.close();
}


void HoI4::decisions::updateDecisions(
	const std::set<std::string>& majorIdeologies,
	const std::map<int, int>& provinceToStateIdMap,
	const Events& theEvents
)
{
	stabilityDecisions.updateDecisions(majorIdeologies);
	politicalDecisions.updateDecisions(majorIdeologies, theEvents);
	exiledGovernmentsDecisions.updateDecisions(majorIdeologies);
	foreignInfluenceDecisions.updateDecisions(majorIdeologies);
	navalTreatyDecisions.updateDecisions(majorIdeologies);
	genericDecisions.updateDecisions(provinceToStateIdMap, majorIdeologies);
}