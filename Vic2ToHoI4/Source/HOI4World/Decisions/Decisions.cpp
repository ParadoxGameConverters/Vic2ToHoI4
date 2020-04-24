#include "Decisions.h"
#include "../Events/Events.h"
#include "Log.h"
#include <regex>



HoI4::decisions::decisions(const Configuration& theConfiguration)
{
	ideologicalCategories = DecisionsCategories::Factory{}.getDecisionsCategories();
	agentRecruitmentDecisions.importDecisions(
		 theConfiguration.getHoI4Path() + "/common/decisions/lar_agent_recruitment_decisions.txt");
	stabilityDecisions.importDecisions(theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt");
	politicalDecisions.importDecisions("ideologicalDecisions.txt");
	exiledGovernmentsDecisions.importDecisions(
		 theConfiguration.getHoI4Path() + "/common/decisions/_exiled_governments_decisions.txt");
	foreignInfluenceDecisions.importDecisions(
		 theConfiguration.getHoI4Path() + "/common/decisions/foreign_influence.txt");
	foreignInfluenceDecisions.importDecisions("DataFiles/foreignInfluenceDecisions.txt");
	navalTreatyDecisions.importDecisions(theConfiguration.getHoI4Path() + "/common/decisions/MTG_naval_treaty.txt");
	resourceProspectingDecisions.importDecisions(
		 theConfiguration.getHoI4Path() + "/common/decisions/resource_prospecting.txt");
	genericDecisions.importDecisions(theConfiguration.getHoI4Path() + "/common/decisions/_generic_decisions.txt");
}


void HoI4::decisions::updateDecisions(const std::set<std::string>& majorIdeologies,
	 const std::map<int, int>& provinceToStateIdMap,
	 const std::map<int, DefaultState>& defaultStates,
	 const Events& theEvents)
{
	LOG(LogLevel::Info) << "\tUpdating decisions";

	generateIdeologicalCategories(majorIdeologies);

	agentRecruitmentDecisions.updateDecisions();
	stabilityDecisions.updateDecisions(majorIdeologies);
	politicalDecisions.updateDecisions(majorIdeologies, theEvents);
	exiledGovernmentsDecisions.updateDecisions(majorIdeologies);
	foreignInfluenceDecisions.updateDecisions(majorIdeologies);
	navalTreatyDecisions.updateDecisions(majorIdeologies);
	resourceProspectingDecisions.updateDecisions(provinceToStateIdMap, defaultStates);
	genericDecisions.updateDecisions(provinceToStateIdMap, majorIdeologies);
}



void HoI4::decisions::generateIdeologicalCategories(const std::set<std::string>& majorIdeologies)
{
	HoI4::DecisionsCategory::Factory decisionsCategoryFactory;

	for (const auto& majorIdeology: majorIdeologies)
	{
		if (majorIdeology == "neutrality")
		{
			continue;
		}

		std::stringstream input;
		input << "= {\n";
		input << "\ticon = " << getIdeologicalIcon(majorIdeology) << "\n";
		input << "\n";
		input << "\tallowed = {\n";
		input << "\t\talways = yes\n";
		input << "\t}\n";
		input << "\n";
		input << "\t#visible = {\n";
		input << "\t#	NOT = { has_government = " << majorIdeology << " }\n";
		input << "\t#	has_idea_with_trait = " << majorIdeology << "_minister\n";
		input << "\t#}\n";
		input << "}\n";
		input << "\n";

		ideologicalCategories->addCategory(
			 decisionsCategoryFactory.getDecisionsCategory(majorIdeology + "_on_the_rise", input));
	}
}


std::string HoI4::decisions::getIdeologicalIcon(const std::string& ideology)
{
	if ((ideology == "fascism") || (ideology == "absolutist"))
	{
		return "generic_fascism";
	}
	if ((ideology == "communism") || (ideology == "radical"))
	{
		return "generic_communism";
	}

	return "generic_democracy";
}