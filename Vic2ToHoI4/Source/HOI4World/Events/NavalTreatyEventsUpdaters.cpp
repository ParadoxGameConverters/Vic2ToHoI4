#include "NavalTreatyEventsUpdaters.h"
#include "EventOption.h"
#include <sstream>



void HoI4::updateNavalTreatyEventOne(Event& event, const std::set<std::string>& majorIdeologies)
{
	event.clearOptions();

	// option A
	EventOption optionA;

	optionA.giveName("MTG_naval_treaty.1.a");

	std::stringstream aiChance;
	aiChance << "= {\n";
	aiChance << "\t\t\tfactor = 70\n";
	aiChance << "\t\t\tmodifier = {\n";
	if (majorIdeologies.contains("democratic"))
	{
		aiChance << "\t\t\t\thas_government = democratic\n";
	}
	aiChance << "\t\t\t\thas_government = neutrality\n";
	aiChance << "\t\t\t\tfactor = 5\n";
	aiChance << "\t\t\t}\n";
	aiChance << "\t\t\tmodifier = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "democratic" || ideology == "neutrality")
		{
			continue;
		}

		aiChance << "\t\t\t\thas_government = " << ideology << "\n";
	}
	aiChance << "\t\t\t\tfactor = 0.25\n";
	aiChance << "\t\t\t}\n";
	aiChance << "\t\t}";
	optionA.giveAiChance(aiChance.str());

	optionA.giveScriptBlock("add_ideas = MTG_naval_treaty_adherent");
	optionA.giveScriptBlock(
		 "modify_global_flag = {\n"
		 "\t\t\tflag = MTG_naval_treaty_signatories\n"
		 "\t\t\tvalue = 1\n"
		 "\t\t}");
	optionA.giveScriptBlock(
		 "every_other_country = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\thas_naval_treaty_trigger = yes\n"
		 "\t\t\t}\n"
		 "\t\t\tcountry_event = { id = MTG_naval_treaty.2 days = 3 }\n"
		 "\t\t\tadd_ai_strategy = {\n"
		 "\t\t\t\ttype = protect\n"
		 "\t\t\t\tid = PREV\n"
		 "\t\t\t\tvalue = 100\n"
		 "\t\t\t}\n"
		 "\t\t}\n");

	event.giveOption(std::move(optionA));

	// option B
	EventOption optionB;

	optionB.giveName("MTG_naval_treaty.1.b");
	optionB.giveAiChance(
		 "= {\n"
		 "\t\t\tfactor = 30\n"
		 "\t\t}");
	optionB.giveScriptBlock("set_country_flag = MTG_refused_naval_treaty");
	optionB.giveScriptBlock(
		 "every_other_country = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\thas_naval_treaty_trigger = yes\n"
		 "\t\t\t}\n"
		 "\t\t\tadd_opinion_modifier = {\n"
		 "\t\t\t\ttarget = PREV\n"
		 "\t\t\t\tmodifier = refused_naval_treaty\n"
		 "\t\t\t}\n"
		 "\t\t\tcountry_event = { id = MTG_naval_treaty.3 days = 3 }\n"
		 "\t\t\tadd_ai_strategy = {\n"
		 "\t\t\t\ttype = contain\n"
		 "\t\t\t\tid = PREV\n"
		 "\t\t\t\tvalue = 100\n"
		 "\t\t\t}\n"
		 "\t\t}");

	event.giveOption(std::move(optionB));
}


void HoI4::updateNavalTreatyEventFour(Event& event, const std::set<std::string>& majorIdeologies)
{
	event.clearOptions();

	// option A
	EventOption optionA;
	optionA.giveName("MTG_naval_treaty.4.a");
	optionA.giveAiChance(
		 "= {\n"
		 "\t\t\tfactor = 70\n"
		 "\t\t}");
	optionA.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\tNOT = { has_naval_treaty_trigger = yes }\n"
		 "\t\t\t}\n"
		 "\t\t\tactivate_mission = MTG_treaty_reduction_mission\n"
		 "\t\t\tFROM = {\n"
		 "\t\t\t\tcountry_event = { id = MTG_naval_treaty.5 days = 3 }\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionA.giveScriptBlock(
		 "else = {\n"
		 "\t\t\tactivate_mission = MTG_treaty_reduction_signatory_mission\n"
		 "\t\t\tFROM = {\n"
		 "\t\t\t\tcountry_event = { id = MTG_naval_treaty.5 days = 3 }\n"
		 "\t\t\t}\n"
		 "\t\t}");
	event.giveOption(std::move(optionA));

	// option B
	EventOption optionB;

	optionB.giveName("MTG_naval_treaty.4.b");

	std::stringstream aiChance;
	aiChance << "= {\n";
	aiChance << "\t\t\tfactor = 30\n";
	if (majorIdeologies.contains("democratic"))
	{
		aiChance << "\t\t\tmodifier = {\n";
		aiChance << "\t\t\t\thas_government = democratic\n";
		aiChance << "\t\t\t\tfactor = 0\n";
		aiChance << "\t\t\t}\n";
	}
	aiChance << "\t\t}";
	optionB.giveAiChance(aiChance.str());

	optionB.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\thas_naval_treaty_trigger = yes\n"
		 "\t\t\t}\n"
		 "\t\t\tadd_stability = -0.1\n"
		 "\t\t\tadd_political_power = -150\n"
		 "\t\t\tremove_naval_treaty_effect = yes\n"
		 "\t\t\tevery_other_country = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_naval_treaty_trigger = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tcountry_event = MTG_naval_treaty.7\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_global_flag = {\n"
		 "\t\t\t\t\t\tflag = MTG_naval_treaty_signatories\n"
		 "\t\t\t\t\t\tvalue < 3\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\trandom_other_country = {\n"
		 "\t\t\t\t\tlimit = {\n"
		 "\t\t\t\t\t\thas_naval_treaty_trigger = yes\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tremove_naval_treaty_effect = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\thidden_effect = { news_event = mtg_news.60 }\n"
		 "\t\t\t\telse = {\n"
		 "\t\t\t\t\tmodify_global_flag = {\n"
		 "\t\t\t\t\t\tflag = MTG_naval_treaty_signatories\n"
		 "\t\t\t\t\t\tvalue = -1\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\tnot = {\n"
		 "\t\t\t\t\t\tany_other_country = {\n"
		 "\t\t\t\t\t\t\tOR = {\n"
		 "\t\t\t\t\t\t\t\thas_idea = MTG_naval_treaty_cheating_reduced\n"
		 "\t\t\t\t\t\t\t\thas_idea = MTG_naval_treaty_adherent_reduced\n"
		 "\t\t\t\t\t\t\t}\n"
		 "\t\t\t\t\t\t}\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tevery_other_country = {\n"
		 "\t\t\t\t\tlimit = {\n"
		 "\t\t\t\t\t\tOR = {\n"
		 "\t\t\t\t\t\t\thas_idea = MTG_naval_treaty_cheating\n"
		 "\t\t\t\t\t\t\thas_idea = MTG_naval_treaty_adherent\n"
		 "\t\t\t\t\t\t}\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t\tactivate_mission = MTG_escalator_clause_invocation_mission\n"
		 "\t\t\t\t\tcustom_effect_tooltip = MTG_escalator_clause_tt\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");

	optionB.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tcountry_event = { id = MTG_naval_treaty.6 days = 3 }\n"
		 "\t\t\teffect_tooltip = {\n"
		 "\t\t\t\tcreate_wargoal = {\n"
		 "\t\t\t\t\ttype = puppet_wargoal_focus\n"
		 "\t\t\t\t\ttarget = PREV\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");

	event.giveOption(std::move(optionB));
}


void HoI4::updateNavalTreatyEventSix(Event& event, const std::set<std::string>& majorIdeologies)
{
	event.clearOptions();

	EventOption optionA;
	optionA.giveName("MTG_naval_treaty.6.a");
	optionA.giveAiChance(
		 "= {\n"
		 "\t\t\tfactor = 70\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\thas_war = yes\n"
		 "\t\t\t\tfactor = 0\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\thas_war_support < 0.2\n"
		 "\t\t\t\tfactor = 0.25\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionA.giveScriptBlock(
		 "create_wargoal = {\n"
		 "\t\t\ttype = puppet_wargoal_focus\n"
		 "\t\t\ttarget = FROM\n"
		 "\t\t}");
	event.giveOption(std::move(optionA));

	EventOption optionB;
	optionB.giveName("MTG_naval_treaty.6.b");
	optionB.giveAiChance(
		 "= {\n"
		 "\t\t\tfactor = 30\n"
		 "\t\t}");
	event.giveOption(std::move(optionB));
}


void HoI4::updateNavalTreatyEventTen(Event& event, const std::set<std::string>& majorIdeologies)
{
	event.giveTrigger(
		 "= {\n"
		 "\t\tany_country = {\n"
		 "\t\t\thas_naval_treaty_trigger = yes\n"
		 "\t\t\thas_war = yes\n"
		 "\t\t\tany_enemy_country = {\n"
		 "\t\t\t\tis_major = yes\n"
		 "\t\t\t}\n"
		 "\t\t}\n"
		 "\t}");
}