#include "DecisionsOutputter.h"
#include "DecisionsCategoriesOutputter.h"
#include <fstream>



void HoI4::outputDecisions(
	decisions& theDecisions,
	const std::set<std::string>& majorIdeologies,
	const Configuration& theConfiguration
)
{
	std::ofstream outStream(
		"output/" + theConfiguration.getOutputName() + "/common/decisions/categories/00_decision_categories.txt",
		std::ostream::app
	);
	outputDecisionCategories(outStream, majorIdeologies);
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/stability_war_support.txt");
	for (const auto& category: theDecisions.getStabilityDecisions())
	{
		outStream << category;
	}
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/political_decisions.txt");
	for (const auto& category: theDecisions.getPoliticalDecisions())
	{
		outStream << category;
	}
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/_exiled_governments_decisions.txt");
	for (const auto& category: theDecisions.getExiledGovernmentsDecisions())
	{
		outStream << category;
	}
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/foreign_influence.txt");
	for (const auto& category: theDecisions.getForeignInfluenceDecisions())
	{
		outStream << category;
	}
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/MTG_naval_treaty.txt");
	for (const auto& category: theDecisions.getNavalTreatyDecisions())
	{
		outStream << category;
	}
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/resource_prospecting.txt");
	for (const auto& category : theDecisions.getResourceProspectingDecisions())
	{
		outStream << category;
	}
	outStream.close();

	outStream.open("output/" + theConfiguration.getOutputName() + "/common/decisions/_generic_decisions.txt");
	for (const auto& category: theDecisions.getGenericDecisions())
	{
		outStream << category;
	}
	outStream.close();
}