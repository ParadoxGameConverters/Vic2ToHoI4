#include "Event.h"
#include "EventOption.h"
#include "GenericEventUpdaters.h"



void HoI4::updateGenericEventOne(Event& eventOne)
{
	eventOne.clearOptions();

	EventOption optionA;
	optionA.giveName("generic.1.a");
	optionA.giveTrigger("has_government = FROM");
	eventOne.giveOption(std::move(optionA));

	EventOption optionB;
	optionB.giveName("generic.1.b");
	optionB.giveTrigger("NOT = { has_government = FROM }");
	eventOne.giveOption(std::move(optionB));
}


void HoI4::updateGenericEventTwo(Event& eventTwo, const std::set<std::string>& majorIdeologies)
{
	eventTwo.clearDescriptions();

	if (majorIdeologies.contains("democratic"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.2.d.a\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = democratic\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = democratic\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventTwo.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("fascism"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.2.d.b\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = fascism\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = fascism\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventTwo.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("communism"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.2.d.c\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = communism\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = communism\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventTwo.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("radical"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.2.d.f\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = radical\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = radical\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventTwo.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("absolutist"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.2.d.g\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = absolutist\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = absolutist\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventTwo.giveDescription(std::move(description));
	}

	std::string description = "= {\n";
	description += "\t\ttext = generic.2.d.e\n";
	description += "\t\ttrigger = {\n";
	description += "\t\t\tNOT = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		description += "\t\t\t\tAND = {\n";
		description += "\t\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\t\thas_government = " + ideology + "\n";
		description += "\t\t\t\t\t}\n";
		description += "\t\t\t\t\thas_government = " + ideology + "\n";
		description += "\t\t\t\t}\n";
	}
	description += "\t\t\t}\n";
	description += "\t\t}\n";
	description += "\t}";
	eventTwo.giveDescription(std::move(description));

	eventTwo.clearOptions();
	if (majorIdeologies.contains("democratic"))
	{
		EventOption option;
		option.giveName("generic.2.a");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = democratic\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = democratic\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock("add_to_faction = FROM");
		option.giveScriptBlock("FROM = { country_event = { id = generic.3 hours = 6 } }");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_inviter@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_applicant@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventTwo.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("fascism"))
	{
		EventOption option;
		option.giveName("generic.2.b");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = fascism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = fascism\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock("add_to_faction = FROM");
		option.giveScriptBlock("FROM = { country_event = { id = generic.3 hours = 6 } }");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_inviter@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_applicant@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventTwo.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("communism"))
	{
		EventOption option;
		option.giveName("generic.2.c");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = communism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = communism\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock("add_to_faction = FROM");
		option.giveScriptBlock("FROM = { country_event = { id = generic.3 hours = 6 } }");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_inviter@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_applicant@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventTwo.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("radical"))
	{
		EventOption option;
		option.giveName("generic.2.g");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = radical\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = radical\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock("add_to_faction = FROM");
		option.giveScriptBlock("FROM = { country_event = { id = generic.3 hours = 6 } }");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_inviter@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_applicant@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventTwo.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("absolutist"))
	{
		EventOption option;
		option.giveName("generic.2.h");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = absolutist\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = absolutist\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock("add_to_faction = FROM");
		option.giveScriptBlock("FROM = { country_event = { id = generic.3 hours = 6 } }");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_inviter@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_applicant@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventTwo.giveOption(std::move(option));
	}

	EventOption bothDifferent;
	bothDifferent.giveName("generic.2.e");
	std::string trigger = "NOT = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		trigger += "\t\t\t\tAND = {\n";
		trigger += "\t\t\t\t\tFROM = {\n";
		trigger += "\t\t\t\t\t\thas_government = " + ideology + "\n";
		trigger += "\t\t\t\t\t}\n";
		trigger += "\t\t\t\t\thas_government = " + ideology + "\n";
		trigger += "\t\t\t\t}\n";
	}
	trigger += "\t\t\t}";
	bothDifferent.giveTrigger(std::move(trigger));
	bothDifferent.giveAiChance(
		 "= {\n"
		 "\t\t\tbase = 100\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_war = no\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\thas_war = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_government = neutrality\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.75\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\tis_major = no\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");
	bothDifferent.giveScriptBlock("add_to_faction = FROM");
	bothDifferent.giveScriptBlock("FROM = { country_event = { id = generic.3 hours = 6 } }");
	bothDifferent.giveHiddenEffect(
		 "= {\n"
		 "\t\t\tset_country_flag = alliance_inviter@ROOT\n"
		 "\t\t\tFROM = { set_country_flag = alliance_applicant@ROOT }\n"
		 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
		 "\t\t}");
	bothDifferent.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tadd_ai_strategy = {\n"
		 "\t\t\t\ttype = alliance\n"
		 "\t\t\t\tid = ROOT\n"
		 "\t\t\t\tvalue = 200\n"
		 "\t\t\t}\n"
		 "\t\t}");
	eventTwo.giveOption(std::move(bothDifferent));

	EventOption reject;
	reject.giveName("generic.2.f");
	reject.giveAiChance(
		 "= {\n"
		 "\t\t\tfactor = 50\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue > 65\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue > 35\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue > 5\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 2.0\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue < 35\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 2.0\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue < 65\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.1\n"
		 "\t\t\t\thas_war = yes\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\thas_war = no\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.1\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\tis_major = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 10\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\tOR = {\n"
		 "\t\t\t\t\t\tis_subject = yes\n"
		 "\t\t\t\t\t\tis_in_faction = yes\n"
		 "\t\t\t\t\t}\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");
	reject.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tcountry_event = { id = generic.4 hours = 6 }\n"
		 "\t\t}");
	eventTwo.giveOption(std::move(reject));
}


void HoI4::updateGenericEventsThreeFourAndSix(Event& event,
	 const int eventNum,
	 const std::set<std::string>& majorIdeologies)
{
	event.clearOptions();
	if (majorIdeologies.contains("democratic"))
	{
		EventOption option;
		option.giveName("generic." + std::to_string(eventNum) + ".a");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = democratic\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = democratic\n"
			 "\t\t\t}");

		event.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("fascism"))
	{
		EventOption option;
		option.giveName("generic." + std::to_string(eventNum) + ".b");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = fascism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = fascism\n"
			 "\t\t\t}");

		event.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("communism"))
	{
		EventOption option;
		option.giveName("generic." + std::to_string(eventNum) + ".c");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = communism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = communism\n"
			 "\t\t\t}");

		event.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("radical"))
	{
		EventOption option;
		option.giveName("generic." + std::to_string(eventNum) + ".f");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = radical\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = radical\n"
			 "\t\t\t}");

		event.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("absolutist"))
	{
		EventOption option;
		option.giveName("generic." + std::to_string(eventNum) + ".g");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = absolutist\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = absolutist\n"
			 "\t\t\t}");

		event.giveOption(std::move(option));
	}

	EventOption option;
	option.giveName("generic." + std::to_string(eventNum) + ".e");
	std::string trigger = "NOT = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		trigger +=
			 "\t\t\t\tAND = {\n"
			 "\t\t\t\t\tFROM = {\n"
			 "\t\t\t\t\t\thas_government = " +
			 ideology +
			 "\n"
			 "\t\t\t\t\t}\n"
			 "\t\t\t\t\thas_government = " +
			 ideology +
			 "\n"
			 "\t\t\t\t}\n";
	}
	trigger += "\t\t\t}";
	option.giveTrigger(std::move(trigger));

	event.giveOption(std::move(option));
}


void HoI4::updateGenericEventFive(Event& eventFive, const std::set<std::string>& majorIdeologies)
{
	eventFive.clearDescriptions();

	if (majorIdeologies.contains("democratic"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.5.d.a\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = democratic\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = democratic\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventFive.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("fascism"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.5.d.b\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = fascism\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = fascism\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventFive.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("communism"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.5.d.c\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = communism\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = communism\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventFive.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("radical"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.5.d.f\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = radical\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = radical\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventFive.giveDescription(std::move(description));
	}
	if (majorIdeologies.contains("absolutist"))
	{
		std::string description = "= {\n";
		description += "\t\ttext = generic.5.d.g\n";
		description += "\t\ttrigger = {\n";
		description += "\t\t\tAND = {\n";
		description += "\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\thas_government = absolutist\n";
		description += "\t\t\t\t}\n";
		description += "\t\t\t\thas_government = absolutist\n";
		description += "\t\t\t}\n";
		description += "\t\t}\n";
		description += "\t}";
		eventFive.giveDescription(std::move(description));
	}

	std::string description = "= {\n";
	description += "\t\ttext = generic.5.d.e\n";
	description += "\t\ttrigger = {\n";
	description += "\t\t\tNOT = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		description += "\t\t\t\tAND = {\n";
		description += "\t\t\t\t\tFROM = {\n";
		description += "\t\t\t\t\t\thas_government = " + ideology + "\n";
		description += "\t\t\t\t\t}\n";
		description += "\t\t\t\t\thas_government = " + ideology + "\n";
		description += "\t\t\t\t}\n";
	}
	description += "\t\t\t}\n";
	description += "\t\t}\n";
	description += "\t}";
	eventFive.giveDescription(std::move(description));

	eventFive.clearOptions();
	if (majorIdeologies.contains("democratic"))
	{
		EventOption option;
		option.giveName("generic.5.a");
		option.giveTrigger(
			 "is_in_faction = no\n"
			 "\t\t\tAND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = democratic\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = democratic\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "FROM = {\n"
			 "\t\t\tfaction_leader = {\n"
			 "\t\t\t\tadd_to_faction = ROOT\n"
			 "\t\t\t}\n"
			 "\t\t\tcountry_event = { id = generic.6 hours = 6 }\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "add_ai_strategy = {\n"
			 "\t\t\ttype = alliance\n"
			 "\t\t\tid = FROM\n"
			 "\t\t\tvalue = 200\n"
			 "\t\t}\n");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_applicant@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_inviter@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventFive.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("fascism"))
	{
		EventOption option;
		option.giveName("generic.5.b");
		option.giveTrigger(
			 "is_in_faction = no\n"
			 "\t\t\tAND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = fascism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = fascism\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "FROM = {\n"
			 "\t\t\tadd_to_faction = ROOT\n"
			 "\t\t\tcountry_event = { id = generic.6 hours = 6 }\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "add_ai_strategy = {\n"
			 "\t\t\ttype = alliance\n"
			 "\t\t\tid = FROM\n"
			 "\t\t\tvalue = 200\n"
			 "\t\t}\n");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_applicant@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_inviter@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventFive.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("communism"))
	{
		EventOption option;
		option.giveName("generic.5.c");
		option.giveTrigger(
			 "is_in_faction = no\n"
			 "\t\t\tAND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = communism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = communism\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "FROM = {\n"
			 "\t\t\tadd_to_faction = ROOT\n"
			 "\t\t\tcountry_event = { id = generic.6 hours = 6 }\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "add_ai_strategy = {\n"
			 "\t\t\ttype = alliance\n"
			 "\t\t\tid = FROM\n"
			 "\t\t\tvalue = 200\n"
			 "\t\t\t}\n");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_applicant@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_inviter@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventFive.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("radical"))
	{
		EventOption option;
		option.giveName("generic.5.h");
		option.giveTrigger(
			 "is_in_faction = no\n"
			 "\t\t\tAND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = radical\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = radical\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "FROM = {\n"
			 "\t\t\tadd_to_faction = ROOT\n"
			 "\t\t\tcountry_event = { id = generic.6 hours = 6 }\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "add_ai_strategy = {\n"
			 "\t\t\ttype = alliance\n"
			 "\t\t\tid = FROM\n"
			 "\t\t\tvalue = 200\n"
			 "\t\t}\n");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_applicant@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_inviter@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventFive.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("absolutist"))
	{
		EventOption option;
		option.giveName("generic.5.i");
		option.giveTrigger(
			 "is_in_faction = no\n"
			 "\t\t\tAND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = absolutist\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = absolutist\n"
			 "\t\t\t}");
		option.giveAiChance(
			 "= {\n"
			 "\t\t\tbase = 100\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "FROM = {\n"
			 "\t\t\tadd_to_faction = ROOT\n"
			 "\t\t\tcountry_event = { id = generic.6 hours = 6 }\n"
			 "\t\t}");
		option.giveScriptBlock(
			 "add_ai_strategy = {\n"
			 "\t\t\ttype = alliance\n"
			 "\t\t\tid = FROM\n"
			 "\t\t\tvalue = 200\n"
			 "\t\t}\n");
		option.giveHiddenEffect(
			 "= {\n"
			 "\t\t\tset_country_flag = alliance_applicant@ROOT\n"
			 "\t\t\tFROM = { set_country_flag = alliance_inviter@ROOT }\n"
			 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
			 "\t\t}");

		eventFive.giveOption(std::move(option));
	}

	EventOption bothDifferent;
	bothDifferent.giveName("generic.5.e");
	std::string trigger =
		 "is_in_faction = no\n"
		 "\t\t\tNOT = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		trigger += "\t\t\t\tAND = {\n";
		trigger += "\t\t\t\t\tFROM = {\n";
		trigger += "\t\t\t\t\t\thas_government = " + ideology + "\n";
		trigger += "\t\t\t\t\t}\n";
		trigger += "\t\t\t\t\thas_government = " + ideology + "\n";
		trigger += "\t\t\t\t}\n";
	}
	trigger += "\t\t\t}";
	bothDifferent.giveTrigger(std::move(trigger));
	bothDifferent.giveAiChance(
		 "= {\n"
		 "\t\t\tbase = 100\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_war = no\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\thas_war = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\tNOT = {\n"
		 "\t\t\t\t\thas_government = neutrality\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.75\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\tis_major = no\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");
	bothDifferent.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tfaction_leader = {\n"
		 "\t\t\t\tadd_to_faction = ROOT\n"
		 "\t\t\t}\n"
		 "\t\t\tcountry_event = { id = generic.6 hours = 6 }\n"
		 "\t\t}");
	bothDifferent.giveHiddenEffect(
		 "= {\n"
		 "\t\t\tset_country_flag = alliance_applicant@ROOT\n"
		 "\t\t\tFROM = { set_country_flag = alliance_inviter@ROOT }\n"
		 "\t\t\tnews_event = { id = news.289 hours = 12 }\n"
		 "\t\t}");
	bothDifferent.giveScriptBlock(
		 "add_ai_strategy = {\n"
		 "\t\t\ttype = alliance\n"
		 "\t\t\tid = FROM\n"
		 "\t\t\tvalue = 200\n"
		 "\t\t}");
	eventFive.giveOption(std::move(bothDifferent));

	EventOption reject;
	reject.giveName("generic.2.f");
	reject.giveAiChance(
		 "= {\n"
		 "\t\t\tfactor = 50\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue > 65\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue > 35\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.5\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue > 5\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 2.0\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue < 35\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 2.0\n"
		 "\t\t\t\thas_opinion = {\n"
		 "\t\t\t\t\ttarget = FROM\n"
		 "\t\t\t\t\tvalue < 65\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.1\n"
		 "\t\t\t\thas_war = yes\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\thas_war = no\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 0.1\n"
		 "\t\t\t\tFROM = {\n"
		 "\t\t\t\t\tis_major = yes\n"
		 "\t\t\t\t}\n"
		 "\t\t\t}\n"
		 "\t\t}");
	reject.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tcountry_event = { id = generic.7 hours = 6 }\n"
		 "\t\t}");
	reject.giveTrigger("is_in_faction = no");
	eventFive.giveOption(std::move(reject));

	EventOption rejectIfInFaction;
	rejectIfInFaction.giveName("generic.2.g");
	rejectIfInFaction.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tcountry_event = { id = generic.7 hours = 6 }\n"
		 "\t\t}");
	rejectIfInFaction.giveTrigger("is_in_faction = yes");
	eventFive.giveOption(std::move(rejectIfInFaction));
}


void HoI4::updateGenericEventSeven(Event& eventSeven, const std::set<std::string>& majorIdeologies)
{
	eventSeven.clearOptions();
	if (majorIdeologies.contains("democratic"))
	{
		EventOption option;
		option.giveName("generic.7.a");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = democratic\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = democratic\n"
			 "\t\t\t}");

		eventSeven.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("fascism"))
	{
		EventOption option;
		option.giveName("generic.4.b");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = fascism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = fascism\n"
			 "\t\t\t}");

		eventSeven.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("communism"))
	{
		EventOption option;
		option.giveName("generic.4.c");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = communism\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = communism\n"
			 "\t\t\t}");

		eventSeven.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("radical"))
	{
		EventOption option;
		option.giveName("generic.4.f");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = radical\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = radical\n"
			 "\t\t\t}");

		eventSeven.giveOption(std::move(option));
	}
	if (majorIdeologies.contains("absolutist"))
	{
		EventOption option;
		option.giveName("generic.4.g");
		option.giveTrigger(
			 "AND = {\n"
			 "\t\t\t\tFROM = {\n"
			 "\t\t\t\t\thas_government = absolutist\n"
			 "\t\t\t\t}\n"
			 "\t\t\t\thas_government = absolutist\n"
			 "\t\t\t}");

		eventSeven.giveOption(std::move(option));
	}

	EventOption option;
	option.giveName("generic.4.e");
	std::string trigger = "NOT = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		trigger +=
			 "\t\t\t\tAND = {\n"
			 "\t\t\t\t\tFROM = {\n"
			 "\t\t\t\t\t\thas_government = " +
			 ideology +
			 "\n"
			 "\t\t\t\t\t}\n"
			 "\t\t\t\t\thas_government = " +
			 ideology +
			 "\n"
			 "\t\t\t\t}\n";
	}
	trigger += "\t\t\t}";
	option.giveTrigger(std::move(trigger));

	eventSeven.giveOption(std::move(option));
}


void HoI4::updateGenericEventFourteen(Event& eventFourteen, const std::set<std::string>& majorIdeologies)
{
	eventFourteen.clearOptions();

	EventOption optionA;
	optionA.giveName("generic.14.a");
	optionA.giveAiChance(
		 "= {\n"
		 "\t\t\tbase = 80\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 1.5\n"
		 "\t\t\t\thas_opinion = { target = FROM value > 50 }\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 1.5\n"
		 "\t\t\t\thas_opinion = { target = FROM value > 75 }\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionA.giveScriptBlock(
		 "random_other_country = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\thas_war_with = FROM\n"
		 "\t\t\t\thas_attache_from = ROOT\n"
		 "\t\t\t}\n"
		 "\t\t\tROOT = { recall_attache = PREV }\n"
		 "\t\t}");
	optionA.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tcountry_event = { id = generic.15 days = 1 }\n"
		 "\t\t}\n");
	optionA.giveScriptBlock("clr_country_flag = object_attache_going_on");
	eventFourteen.giveOption(std::move(optionA));

	EventOption optionB;
	optionB.giveName("generic.14.b");
	optionB.giveAiChance(
		 "= {\n"
		 "\t\t\tbase = 20\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 2\n"
		 "\t\t\t\thas_opinion = { target = FROM value < 0 }\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 3\n"
		 "\t\t\t\thas_opinion = { target = FROM value < -20 }\n"
		 "\t\t\t}\n"
		 "\t\t\tmodifier = {\n"
		 "\t\t\t\tfactor = 3\n"
		 "\t\t\t\thas_opinion = { target = FROM value < -50 }\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionB.giveScriptBlock("custom_effect_tooltip = attache_political_power_tt");
	optionB.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\tNOT = { strength_ratio = { tag = FROM ratio < 3 } }\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > -25 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 0 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -5\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > 0 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -10\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\tadd_political_power = -15\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionB.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 3 }\n"
		 "\t\t\t\tNOT = { strength_ratio = { tag = FROM ratio < 2.5 } }\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > -25 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 0 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -10\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > 0 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -20\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\tadd_political_power = -30\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionB.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 2.5 }\n"
		 "\t\t\t\tNOT = { strength_ratio = { tag = FROM ratio < 2 } }\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > -25 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 0 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -15\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > 0 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -30\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\tadd_political_power = -45\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionB.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 2 }\n"
		 "\t\t\t\tNOT = { strength_ratio = { tag = FROM ratio < 1.5 } }\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > -25 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 0 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -20\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > 0 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -40\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\tadd_political_power = -60\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionB.giveScriptBlock(
		 "if = {\n"
		 "\t\t\tlimit = {\n"
		 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 1.5 }\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > -25 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 0 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -25\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = {\n"
		 "\t\t\t\t\thas_opinion = { target = FROM value > 0 }\n"
		 "\t\t\t\t\tNOT = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\tadd_political_power = -50\n"
		 "\t\t\t}\n"
		 "\t\t\tif = {\n"
		 "\t\t\t\tlimit = { has_opinion = { target = FROM value > 50 } }\n"
		 "\t\t\t\tadd_political_power = -75\n"
		 "\t\t\t}\n"
		 "\t\t}");
	optionB.giveScriptBlock(
		 "FROM = {\n"
		 "\t\t\tadd_opinion_modifier = { target = ROOT modifier = rejected_demands }\n"
		 "\t\t\tcountry_event = { id = generic.16 days = 1 }\n"
		 "\t\t}");

	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		optionB.giveScriptBlock(
			 "if = {\n"
			 "\t\t\tlimit = {\n"
			 "\t\t\t\tFROM = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\tNOT = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\t" +
			 ideology +
			 " > 0.1\n"
			 "\t\t\t\tNOT = { " +
			 ideology +
			 " > 0.2 }\n"
			 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 1.2 }\n"
			 "\t\t\t}\n"
			 "\t\t\tcustom_effect_tooltip = attache_" +
			 ideology +
			 "_tt\n"
			 "\t\t\tadd_stability = -0.025\n"
			 "\t\t}");
		optionB.giveScriptBlock(
			 "if = {\n"
			 "\t\t\tlimit = {\n"
			 "\t\t\t\tFROM = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\tNOT = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\t" +
			 ideology +
			 " > 0.2\n"
			 "\t\t\t\tNOT = { " +
			 ideology +
			 " > 0.3 }\n"
			 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 1.2 }\n"
			 "\t\t\t}\n"
			 "\t\t\tcustom_effect_tooltip = attache_" +
			 ideology +
			 "_tt\n"
			 "\t\t\tadd_stability = -0.05\n"
			 "\t\t}");
		optionB.giveScriptBlock(
			 "if = {\n"
			 "\t\t\tlimit = {\n"
			 "\t\t\t\tFROM = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\tNOT = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\t" +
			 ideology +
			 " > 0.3\n"
			 "\t\t\t\tNOT = { " +
			 ideology +
			 " > 0.4 }\n"
			 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 1.2 }\n"
			 "\t\t\t}\n"
			 "\t\t\tcustom_effect_tooltip = attache_" +
			 ideology +
			 "_tt\n"
			 "\t\t\tadd_stability = -0.075\n"
			 "\t\t}");
		optionB.giveScriptBlock(
			 "if = {\n"
			 "\t\t\tlimit = {\n"
			 "\t\t\t\tFROM = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\tNOT = { has_government = " +
			 ideology +
			 " }\n"
			 "\t\t\t\t" +
			 ideology +
			 " > 0.4\n"
			 "\t\t\t\tstrength_ratio = { tag = FROM ratio < 1.2 }\n"
			 "\t\t\t}\n"
			 "\t\t\tcustom_effect_tooltip = attache_" +
			 ideology +
			 "_tt\n"
			 "\t\t\tadd_stability = -0.1\n"
			 "\t\t}");
	}
	optionB.giveHiddenEffect(
		 "= {\n"
		 "\t\t\tset_country_flag = { flag = rejected_withdrawing_attache value = 1 days = 90 }\n"
		 "\t\t\tset_country_flag = { flag = rejected_withdrawing_attache@FROM value = 1 days = 365 }\n"
		 "\t\t\tclr_country_flag = object_attache_going_on\n"
		 "\t\t}");


	eventFourteen.giveOption(std::move(optionB));
}