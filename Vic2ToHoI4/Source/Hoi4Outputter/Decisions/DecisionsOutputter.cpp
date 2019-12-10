#include "DecisionsOutputter.h"
#include <fstream>



void HoI4::outputDecisions(const decisions& theDecisions, const Configuration& theConfiguration)
{
	std::ofstream outStream(
		"output/" + theConfiguration.getOutputName() + "/common/decisions/categories/00_decision_categories.txt",
		std::ostream::app
	);
	outStream << theDecisions.getDecisionsCategories();
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
	for (const auto& category : theDecisions.getExiledGovernmentsDecisions())
	{
		outStream << category;
	}
	outStream.close();
}
