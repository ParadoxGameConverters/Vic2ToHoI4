#include "src/HOI4World/Factions/FactionTemplates.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include <ranges>



HoI4::FactionTemplates::FactionTemplates()
{
	Log(LogLevel::Info) << "\tImporting faction templates";

	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		const FactionTemplates& ideologyTemplates(theStream);
		for (const auto& factionTemplate: ideologyTemplates.ideologicalTemplates)
		{
			importedTemplates[ideology].push_back(std::make_shared<FactionTemplate>(factionTemplate));
		}
	});
	parseFile(std::filesystem::path("Configurables") / "ideological_faction_templates.txt");
}


HoI4::FactionTemplates::FactionTemplates(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& theStream) {
		ideologicalTemplates.push_back(FactionTemplate(id, theStream));
	});
	parseStream(theStream);
}


void HoI4::FactionTemplates::updateFactionTemplates(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating ideological faction templates";

	updateFactionTemplateDemocratic(majorIdeologies);
	updateFactionTemplateFascism(majorIdeologies);
	updateFactionTemplateRadical(majorIdeologies);
	updateFactionTemplateAbsolutist(majorIdeologies);
	updateFactionTemplateNeutrality(majorIdeologies);
	updateFactionTemplateRegional(majorIdeologies);
	updateFactionTemplateEuropeanUnity(majorIdeologies);
	updateFactionTemplateEuropeanDominanceMonarchist(majorIdeologies);

	for (const auto& ideology: majorIdeologies)
	{
		for (const auto& factionTemplate: importedTemplates.at(ideology))
		{
			ideologicalTemplates.push_back(*factionTemplate);
		}
	}
}


std::shared_ptr<HoI4::FactionTemplate> HoI4::FactionTemplates::getTemplate(const std::string& templateId)
{
	for (auto& templates: importedTemplates | std::views::values)
	{
		for (auto& factionTemplate: templates)
		{
			if (factionTemplate->getId() == templateId)
			{
				return factionTemplate;
			}
		}
	}

	return nullptr;
}


void HoI4::FactionTemplates::updateFactionTemplateDemocratic(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_democratic");
		 factionTemplate && !majorIdeologies.contains("fascism"))
	{
		factionTemplate->removeRule("joining_rule_non_fascist");
	}
}


void HoI4::FactionTemplates::updateFactionTemplateFascism(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_fascism");
		 factionTemplate && !majorIdeologies.contains("communism"))
	{
		factionTemplate->removeRule("joining_rule_non_communist");
	}
}

void HoI4::FactionTemplates::updateFactionTemplateRadical(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_radical"); factionTemplate)
	{
		if (!majorIdeologies.contains("democratic"))
		{
			factionTemplate->removeGoal("faction_goal_war_on_democracy");
		}
		if (!majorIdeologies.contains("communism"))
		{
			factionTemplate->removeRule("joining_rule_non_democratic");
		}
	}
}


void HoI4::FactionTemplates::updateFactionTemplateAbsolutist(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_absolutist");
		 factionTemplate && !majorIdeologies.contains("communism"))
	{
		factionTemplate->removeRule("joining_rule_non_communist");
	}
}


void HoI4::FactionTemplates::updateFactionTemplateNeutrality(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_neutrality");
		 factionTemplate && !majorIdeologies.contains("democratic"))
	{
		factionTemplate->removeRule("joining_rule_democratic_non_aligned");
		factionTemplate->addRule("joining_rule_same_ideology");
	}
}

void HoI4::FactionTemplates::updateFactionTemplateRegional(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_regional"); factionTemplate)
	{
		std::string visibleStr = "= {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if (ideology == "neutrality" || ideology == "democratic")
			{
				continue;
			}
			visibleStr += "\t\tNOT = { has_government = " + ideology + " }\n";
		}
		visibleStr += "\t\tNOT = { capital_scope = { is_on_continent = europe } }\n";
		visibleStr += "\t}\n";
		factionTemplate->setVisible(visibleStr);
	}
}


void HoI4::FactionTemplates::updateFactionTemplateEuropeanUnity(const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_european_unity"); factionTemplate)
	{
		std::string visibleStr = "= {\n";
		visibleStr += "\t\tcapital_scope = {\n";
		visibleStr += "\t\t\tis_on_continent = europe\n";
		visibleStr += "\t\t}\n";
		if (majorIdeologies.contains("fascism"))
		{
			visibleStr += "\t\tNOT = {\n";
			visibleStr += "\t\t\thas_government = fascism \n";
			visibleStr += "\t\t}\n";
		}
		visibleStr += "\t}\n";
		factionTemplate->setVisible(visibleStr);

		std::string availableStr = "= {\n";
		if (majorIdeologies.contains("fascism"))
		{
			availableStr += "\t\tNOT = {\n";
			availableStr += "\t\t\thas_government = fascism \n";
			availableStr += "\t\t}\n";
		}
		availableStr += "\t}\n";
		factionTemplate->setAvailable(availableStr);
	}
}


void HoI4::FactionTemplates::updateFactionTemplateEuropeanDominanceMonarchist(
	 const std::set<std::string>& majorIdeologies)
{
	if (auto factionTemplate = getTemplate("faction_template_european_dominance_monarchist");
		 factionTemplate && !majorIdeologies.contains("communism"))
	{
		factionTemplate->removeGoal("faction_goal_defeat_of_communism");

		const std::vector<std::string> evilIdeologiesSorted = {"fascism", "radical", "absolutist"};
		for (const auto& ideology: evilIdeologiesSorted)
		{
			if (majorIdeologies.contains(ideology))
			{
				factionTemplate->addGoal("faction_goal_defeat_of_" + ideology);
				break;
			}
		}
	}
}