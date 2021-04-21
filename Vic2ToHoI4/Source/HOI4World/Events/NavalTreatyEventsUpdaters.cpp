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