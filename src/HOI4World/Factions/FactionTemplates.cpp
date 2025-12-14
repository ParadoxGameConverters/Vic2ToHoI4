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