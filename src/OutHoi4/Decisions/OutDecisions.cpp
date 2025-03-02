#include "src/OutHoi4/Decisions/OutDecisions.h"
#include "src/OutHoi4/Decisions/OutDecisionsCategories.h"
#include <fstream>



void HoI4::outputDecisions(const decisions& theDecisions,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName)
{
	outputDecisionCategories("output" / outputName / "common/decisions/categories/00_decision_categories.txt",
		 theDecisions.getIdeologicalCategories());

	const std::filesystem::path agents_filename =
		 "output" / outputName / "common/decisions/lar_agent_recruitment_decisions.txt";
	std::ofstream outStream(agents_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + agents_filename.string());
	}
	for (const auto& category: theDecisions.getAgentRecruitmentDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path stability_war_support_filename =
		 "output" / outputName / "common/decisions/stability_war_support.txt";
	outStream.open(stability_war_support_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + stability_war_support_filename.string());
	}
	for (const auto& category: theDecisions.getStabilityDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path political_decisions_filename =
		 "output" / outputName / "common/decisions/political_decisions.txt";
	outStream.open(political_decisions_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + political_decisions_filename.string());
	}
	for (const auto& category: theDecisions.getPoliticalDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path exiled_governments_decisions_filename =
		 "output" / outputName / "common/decisions/_exiled_governments_decisions.txt";
	outStream.open(exiled_governments_decisions_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + exiled_governments_decisions_filename.string());
	}
	for (const auto& category: theDecisions.getExiledGovernmentsDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path foreign_influence_filename =
		 "output" / outputName / "common/decisions/foreign_influence.txt";
	outStream.open(foreign_influence_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + foreign_influence_filename.string());
	}
	for (const auto& category: theDecisions.getForeignInfluenceDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path MTG_naval_treaty_filename =
		 "output" / outputName / "common/decisions/MTG_naval_treaty.txt";
	outStream.open(MTG_naval_treaty_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + MTG_naval_treaty_filename.string());
	}
	for (const auto& category: theDecisions.getNavalTreatyDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path resource_prospecting_filename =
		 "output" / outputName / "common/decisions/resource_prospecting.txt";
	outStream.open(resource_prospecting_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + resource_prospecting_filename.string());
	}
	for (const auto& category: theDecisions.getResourceProspectingDecisions())
	{
		outStream << category;
	}
	outStream.close();

	const std::filesystem::path generic_decisions_filename =
		 "output" / outputName / "common/decisions/_generic_decisions.txt";
	outStream.open(generic_decisions_filename);
	if (!outStream.is_open())
	{
		throw std::runtime_error("Could not open " + generic_decisions_filename.string());
	}
	for (const auto& category: theDecisions.getGenericDecisions())
	{
		outStream << category;
	}
	outStream.close();
}