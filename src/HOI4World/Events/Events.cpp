#include "src/HOI4World/Events/Events.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Configuration.h"
#include "src/HOI4World/Events/CapitulationEvents.h"
#include "src/HOI4World/Events/EventHelpers.h"
#include "src/HOI4World/Events/EventsFile.h"
#include "src/HOI4World/Events/GenericEventUpdaters.h"
#include "src/HOI4World/Events/LarOccupationEvents.h"
#include "src/HOI4World/Events/NavalTreatyEventsUpdaters.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/HoI4Localisation.h"
#include "src/HOI4World/OnActions/OnActions.h"
#include "src/V2World/Countries/Country.h"
#include "src/V2World/Politics/Party.h"
#include <fstream>



void HoI4::Events::createSummitNewsEvents(const std::set<std::string>& majorIdeologies)
{
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology != "fascism" && ideology != "communism" || summitNewsEventsIds.contains(ideology))
		{
			continue;
		}
		Event newsEvent;
		newsEvent.giveType("news_event");
		newsEvent.giveId("news." + std::to_string(newsEventNumber));
		if (ideology == "fascism")
		{
			newsEvent.giveTitle("fascist_summit.t");
			newsEvent.givePicture("GFX_news_event_fascist_gathering");
		}
		else if (ideology == "communism")
		{
			newsEvent.giveTitle("communist_summit.t");
			newsEvent.givePicture("GFX_news_event_generic_rally_3");
		}
		newsEvent.giveDescription("= fascist_summit.d");
		newsEvent.setTriggeredOnly();
		EventOption optionA;
		optionA.giveName("fascist_summit.a");
		optionA.giveScriptBlock("effect_tooltip = { FROM = { add_threat = 3 } }");
		newsEvent.giveOption(std::move(optionA));
		newsEvents.push_back(newsEvent);
		summitNewsEventsIds[ideology] = newsEvent.getId();
		newsEventNumber++;
	}
}



void HoI4::Events::createFactionEvents(const Country& leader, Mappers::FactionNameMapper& factionNameMapper)
{
	const auto& leaderTag = leader.getTag();

	const auto& possibleFactionName = factionNameMapper.getFactionName(leader.getGovernmentIdeology(),
		 leader.getPrimaryCulture(),
		 leader.getPrimaryCultureGroup());
	std::string factionName;
	if (possibleFactionName)
	{
		factionName = *possibleFactionName;
	}
	else
	{
		factionName = "Faction of [" + leaderTag + ".GetName]";
	}

	Event nfEvent;
	nfEvent.giveType("country_event");
	nfEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber++));
	nfEvent.giveTitle("\"Alliance Offer\"");
	nfEvent.giveDescription(
		 "= \"We have been invited to an alliance with [" + leaderTag + ".GetName]. Should we accept the invitation?\"");
	nfEvent.givePicture("news_event_generic_sign_treaty1");
	nfEvent.setTriggeredOnly();
	EventOption yesOption;
	yesOption.giveName("\"Yes\"");
	std::string createFaction = "if = {\n";
	createFaction += "\t\t\tlimit = {\n";
	createFaction += "\t\t\t\t" + leaderTag + " = {\n";
	createFaction += "\t\t\t\t\tis_faction_leader = no\n";
	createFaction += "\t\t\t\t}\n";
	createFaction += "\t\t\t}\n";
	createFaction += "\t\t\t" + leaderTag + " = {\n";
	createFaction += "\t\t\t\tleave_faction = yes\n";
	createFaction += "\t\t\t\tcreate_faction = \"" + factionName + "\"\n";
	createFaction += "\t\t\t}\n";
	createFaction += "\t\t}";
	yesOption.giveScriptBlock(std::move(createFaction));
	auto addToFaction = leaderTag + " = {\n";
	addToFaction += "\t\t\tadd_to_faction = ROOT\n";
	addToFaction += "\t\t}";
	yesOption.giveScriptBlock(std::move(addToFaction));
	yesOption.giveHiddenEffect(
		 "= {\n"
		 "\t\t\tnews_event = { id = news." +
		 std::to_string(newsEventNumber) +
		 " }\n"
		 "\t\t}");
	std::string yesOptionChance;
	yesOptionChance = "= {\n";
	yesOptionChance += "\t\t\tfactor = 3\n";
	yesOptionChance += "\t\t\tmodifier = {\n";
	yesOptionChance += "\t\t\t\tfactor = 0\n";
	yesOptionChance += "\t\t\t\tNOT = { has_government = " + leaderTag + " }\n";
	yesOptionChance += "\t\t\t}\n";
	yesOptionChance += "\t\t\tmodifier = {\n";
	yesOptionChance += "\t\t\t\tfactor = 0.5\n";
	yesOptionChance += "\t\t\t\thas_opinion = {\n";
	yesOptionChance += "\t\t\t\t\ttarget = " + leaderTag + "\n";
	yesOptionChance += "\t\t\t\t\tvalue < 100\n";
	yesOptionChance += "\t\t\t\t}\n";
	yesOptionChance += "\t\t\t}\n";
	yesOptionChance += "\t\t\tmodifier = {\n";
	yesOptionChance += "\t\t\t\tfactor = 0.5\n";
	yesOptionChance += "\t\t\t\thas_opinion = {\n";
	yesOptionChance += "\t\t\t\t\ttarget = " + leaderTag + "\n";
	yesOptionChance += "\t\t\t\t\tvalue < 50\n";
	yesOptionChance += "\t\t\t\t}\n";
	yesOptionChance += "\t\t\t}\n";
	yesOptionChance += "\t\t\tmodifier = {\n";
	yesOptionChance += "\t\t\t\tfactor = 0\n";
	yesOptionChance += "\t\t\t\thas_opinion = {\n";
	yesOptionChance += "\t\t\t\t\ttarget = " + leaderTag + "\n";
	yesOptionChance += "\t\t\t\t\tvalue < 0\n";
	yesOptionChance += "\t\t\t\t}\n";
	yesOptionChance += "\t\t\t}\n";
	yesOptionChance += "\t\t}\n";
	yesOption.giveAiChance(std::move(yesOptionChance));
	nfEvent.giveOption(std::move(yesOption));
	EventOption noOption;
	noOption.giveName("\"No\"");
	noOption.giveAiChance("= { factor = 1 }");
	noOption.giveHiddenEffect(
		 "= {\n"
		 "\t\t\tnews_event = { id = news." +
		 std::to_string(newsEventNumber + 1) +
		 " }\n"
		 "\t\t}");
	nfEvent.giveOption(std::move(noOption));
	nationalFocusEvents.push_back(nfEvent);

	Event newsEventYes;
	newsEventYes.giveType("news_event");
	newsEventYes.giveId("news." + std::to_string(newsEventNumber));
	newsEventYes.giveTitle("\"[From.GetName] formalizes alliance with [" + leaderTag + ".GetName]\"");
	newsEventYes.giveDescription(
		 "= \"The leaders of both countries have announced their intent of military cooperation.\"");
	newsEventYes.givePicture("news_event_generic_sign_treaty1");
	newsEventYes.setMajor();
	newsEventYes.setTriggeredOnly();
	EventOption interestingOption;
	interestingOption.giveName("\"Interesting\"");
	newsEventYes.giveOption(std::move(interestingOption));
	newsEvents.push_back(newsEventYes);

	Event newsEventNo;
	newsEventNo.giveType("news_event");
	newsEventNo.giveId("news." + std::to_string(newsEventNumber + 1));
	newsEventNo.giveTitle("\"[From.GetName] refuses the alliance offer of [" + leaderTag + ".GetName]\"");
	newsEventNo.giveDescription("= \"The alliance negotiations ended in disagreement.\"");
	newsEventNo.givePicture("news_event_generic_sign_treaty1");
	newsEventNo.setMajor();
	newsEventNo.setTriggeredOnly();
	EventOption interestingOption2;
	interestingOption2.giveName("\"Interesting\"");
	newsEventNo.giveOption(std::move(interestingOption2));
	newsEvents.push_back(newsEventNo);

	newsEventNumber += 2;
}


void HoI4::Events::createAnnexEvent(const Country& annexer, const Country& annexed)
{
	auto possibleAnnexerName = annexer.getName();
	std::string annexerName;
	if (possibleAnnexerName)
	{
		annexerName = *possibleAnnexerName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexer name for annexation events";
		annexerName.clear();
	}

	auto possibleAnnexedName = annexed.getName();
	std::string annexedName;
	if (possibleAnnexedName)
	{
		annexedName = *possibleAnnexedName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexed country name for annexation events";
		annexedName.clear();
	}

	const auto& annexerTag = annexer.getTag();
	const auto& annexedTag = annexed.getTag();

	Event annexEvent;
	annexEvent.giveType("country_event");
	annexEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber));
	annexEvent.giveTitle("\"[" + annexerTag + ".GetName] Demands [" + annexedTag + ".GetName]!\"");
	auto description = "= \"Today [" + annexerTag + ".GetName] sent an envoy to us with a proposition of an union. ";
	description +=
		 "We are alone and in this world, and a union with [" + annexerTag + ".GetName might prove to be fruitful. ";
	description += "Our people would be safe with the mighty army of [" + annexerTag +
						".GetName] and we could possibly flourish with their established economy. Or we could refuse the "
						"union which would surely lead to war, but maybe we can hold them off!\"";
	annexEvent.giveDescription(std::move(description));
	annexEvent.givePicture("GFX_report_event_hitler_parade");
	annexEvent.setTriggeredOnly();

	EventOption acceptOption;
	acceptOption.giveName("\"We accept the Union\"");
	std::string acceptAiChance = "= {\n";
	acceptAiChance += "\t\t\tbase = 30\n";
	acceptAiChance += "\t\t\tmodifier = {\n";
	acceptAiChance += "\t\t\t\tfactor = 0\n";
	acceptAiChance += "\t\t\t\t" + annexed.getTag() + " = { is_subject = yes }\n";
	acceptAiChance += "\t\t\t}\n";
	acceptAiChance += "\t\t\tmodifier = {\n";
	acceptAiChance += "\t\t\t\tfactor = 0\n";
	acceptAiChance += "\t\t\t\tNOT = { tag = " + annexedTag + " }\n";
	acceptAiChance += "\t\t\t\t" + annexerTag + " = { on_same_continent = no }\n";
	acceptAiChance += "\t\t\t}\n";
	acceptAiChance += "\t\t\tmodifier = {\n";
	acceptAiChance += "\t\t\t\tadd = -15\n";
	acceptAiChance += "\t\t\t\t" + annexer.getTag() + " = { has_army_size = { size < 40 } }\n";
	acceptAiChance += "\t\t\t}\n";
	acceptAiChance += "\t\t\tmodifier = {\n";
	acceptAiChance += "\t\t\t\tadd = 45\n";
	acceptAiChance += "\t\t\t\t" + annexer.getTag() + " = { has_army_size = { size > 39 } }\n";
	acceptAiChance += "\t\t\t}\n";
	acceptAiChance += "\t\t}";
	acceptOption.giveAiChance(std::move(acceptAiChance));
	std::string acceptNewsEvent = "FROM = {\n";
	acceptNewsEvent +=
		 "\t\t\tcountry_event = { "
		 "hours = 2 "
		 "id = NFEvents." +
		 std::to_string(nationalFocusEventNumber + 1) +
		 " "
		 "}\n";
	acceptNewsEvent += "\t\t}";
	acceptOption.giveScriptBlock(std::move(acceptNewsEvent));
	std::string tooltip = "custom_effect_tooltip = GAME_OVER_TT";
	acceptOption.giveScriptBlock(std::move(tooltip));
	annexEvent.giveOption(std::move(acceptOption));

	EventOption refuseOption;
	refuseOption.giveName("\"We Refuse!\"");
	std::string refuseAiChance = "= {\n";
	refuseAiChance += "\t\t\tbase = 10\n";
	refuseAiChance += "\t\t\tmodifier = {\n";
	refuseAiChance += "\t\t\t\tfactor = 0\n";
	refuseAiChance += "\t\t\t\t" + annexer.getTag() + " = { has_army_size = { size > 39 } }\n";
	refuseAiChance += "\t\t\t}\n";
	refuseAiChance += "\t\t\tmodifier = {\n";
	refuseAiChance += "\t\t\t\tadd = 20\n";
	refuseAiChance += "\t\t\t\t" + annexer.getTag() + " = { has_army_size = { size < 30 } }\n";
	refuseAiChance += "\t\t\t}\n";
	refuseAiChance += "\t\t}";
	refuseOption.giveAiChance(std::move(refuseAiChance));
	std::string removeFromFaction = "FROM = {\n";
	removeFromFaction +=
		 "\t\t\tcountry_event = { "
		 "hours = 2 "
		 "id = NFEvents." +
		 std::to_string(nationalFocusEventNumber + 2) +
		 " "
		 "}\n";
	removeFromFaction += "\t\t\tif = {\n";
	removeFromFaction += "\t\t\t\tlimit = { is_in_faction_with = " + annexed.getTag() + " }\n";
	removeFromFaction += "\t\t\t\tremove_from_faction = " + annexed.getTag() + "\n";
	removeFromFaction += "\t\t\t}\n";
	removeFromFaction += "\t\t}";
	refuseOption.giveScriptBlock(std::move(removeFromFaction));
	annexEvent.giveOption(std::move(refuseOption));

	nationalFocusEvents.push_back(annexEvent);


	Event refusedEvent;
	refusedEvent.giveType("country_event");
	refusedEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber + 2));
	refusedEvent.giveTitle("\"[FROM.GetName] Refuses!\"");
	refusedEvent.giveDescription(
		 "= \"[FROM.GetName] Refused our proposed union! This is an insult to us that cannot go unanswered!\"");
	refusedEvent.givePicture("GFX_report_event_german_troops");
	refusedEvent.setTriggeredOnly();

	EventOption refusedOption;
	refusedOption.giveName("\"It's time for war\"");
	std::string wargoal = "create_wargoal = {\n";
	wargoal += "\t\t\ttype = annex_everything\n";
	wargoal += "\t\t\ttarget = FROM\n";
	wargoal += "\t\t}";
	refusedOption.giveScriptBlock(std::move(wargoal));
	refusedOption.giveScriptBlock("news_event = { id = static_news.3 hours = 6 }");
	refusedEvent.giveOption(std::move(refusedOption));

	nationalFocusEvents.push_back(refusedEvent);


	Event acceptedEvent;
	acceptedEvent.giveType("country_event");
	acceptedEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber + 1));
	acceptedEvent.giveTitle("\"[FROM.GetName] accepts!\"");
	acceptedEvent.giveDescription(
		 "= \"[FROM.GetName] accepted our proposed union, their added strength will push us to greatness!\"");
	acceptedEvent.givePicture("GFX_report_event_german_speech");
	acceptedEvent.setTriggeredOnly();

	EventOption acceptedOption;
	acceptedOption.giveName("\"A stronger Union!\"");
	std::string effect;
	effect += "every_country = {\n";
	effect += "\t\t\tlimit = { is_subject_of = " + annexedTag + " }\n";
	effect += "\t\t\tcountry_event = NFEvents." + std::to_string(nationalFocusEventNumber) + "\n";
	effect += "\t\t}\n";
	effect += "\t\tFROM = {\n";
	effect += "\t\t\tevery_owned_state = {\n";
	effect += "\t\t\t\tadd_core_of = " + annexerTag + "\n";
	effect += "\t\t\t}\n";
	effect += "\t\t}\n";
	effect += "\t\tif = {\n";
	effect += "\t\t\tlimit = { FROM = { tag = " + annexedTag + " } }\n";
	effect += "\t\t\tannex_country = { target = " + annexedTag + " transfer_troops = yes }\n";
	effect += "\t\t\tadd_political_power = 50\n";
	effect += "\t\t\tadd_named_threat = { threat = 2 name = \"" + annexerName + " annexed " + annexedName + "\" }\n";
	effect += "\t\t\tnews_event = { id = static_news.2 hours = 6 }\n";
	effect += "\t\t\tset_country_flag = " + annexedTag + "_annexed\n";
	effect += "\t\t}\n";
	effect += "\t\telse = {\n";
	effect += "\t\t\tpuppet = FROM\n";
	effect += "\t\t}\n";
	acceptedOption.giveScriptBlock(std::move(effect));
	acceptedEvent.giveOption(std::move(acceptedOption));

	nationalFocusEvents.push_back(acceptedEvent);


	nationalFocusEventNumber += 3;
}


void HoI4::Events::createSudetenEvent(const std::string& annexerTag,
	 const std::string& annexedTag,
	 const std::vector<int>& claimedStates)
{
	Event sudetenEvent;
	sudetenEvent.giveType("country_event");
	sudetenEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber));
	sudetenEvent.giveTitle("\"[" + annexerTag + ".GetName] Demands [" + annexedTag + ".GetName]!\"");
	auto description =
		 "= \"[" + annexerTag +
		 ".GetName] has recently been making claims to our bordering states, saying that these states are full of [" +
		 annexerTag +
		 ".GetAdjective] people and that the territory should be given to them. Although it is true that recently our "
		 "neighboring states have had an influx of [" +
		 annexerTag + ".GetAdjective] people in the recent years, we cannot give up our lands because a few [" +
		 annexerTag + ".GetAdjective] settled down in our land. In response [" + annexerTag +
		 ".GetName] has called for a conference, demanding their territory in exchange for peace. How do we respond? Our "
		 "people would be safe with the mighty army of [" +
		 annexerTag +
		 ".GetName] and we could possibly flourish with their established economy. Or we could refuse the union which "
		 "would surely lead to war, but maybe we can hold them off!\"";
	sudetenEvent.giveDescription(std::move(description));
	sudetenEvent.givePicture("GFX_report_event_hitler_parade");
	sudetenEvent.setTriggeredOnly();

	EventOption acceptOption;
	acceptOption.giveName("\"We Accept\"");
	std::string acceptAiChance = "= {\n";
	acceptAiChance += "\t\t\tbase = 30\n";
	acceptAiChance += "\t\t\tmodifier = {\n";
	acceptAiChance += "\t\t\t\tadd = -15\n";
	acceptAiChance += "\t\t\t\t" + annexerTag + " = { has_army_size = { size < 40 } }\n";
	acceptAiChance += "\t\t\t}\n";
	acceptAiChance += "\t\t\tmodifier = {\n";
	acceptAiChance += "\t\t\t\tadd = 45\n";
	acceptAiChance += "\t\t\t\t" + annexerTag + " = { has_army_size = { size > 39 } }\n";
	acceptAiChance += "\t\t\t}\n";
	acceptAiChance += "\t\t}";
	acceptOption.giveAiChance(std::move(acceptAiChance));
	auto acceptNewsEvent = annexerTag + " = {\n";
	acceptNewsEvent +=
		 "\t\t\tcountry_event = { "
		 "hours = 2 "
		 "id = NFEvents." +
		 std::to_string(nationalFocusEventNumber + 1) +
		 " "
		 "}\n";
	acceptNewsEvent += "\t\t}";
	acceptOption.giveScriptBlock(std::move(acceptNewsEvent));
	sudetenEvent.giveOption(std::move(acceptOption));

	EventOption refuseOption;
	refuseOption.giveName("\"We Refuse!\"");
	std::string refuseAiChance = " = {\n";
	refuseAiChance += "\t\t\tbase = 10\n";
	refuseAiChance += "\t\t\tmodifier = {\n";
	refuseAiChance += "\t\t\t\tfactor = 0\n";
	refuseAiChance += "\t\t\t\t" + annexerTag + " = { has_army_size = { size > 39 } }\n";
	refuseAiChance += "\t\t\t}\n";
	refuseAiChance += "\t\t\tmodifier = {\n";
	refuseAiChance += "\t\t\t\tadd = 20\n";
	refuseAiChance += "\t\t\t\t" + annexerTag + " = { has_army_size = { size < 30 } }\n";
	refuseAiChance += "\t\t\t}\n";
	refuseAiChance += "\t\t}";
	refuseOption.giveAiChance(std::move(refuseAiChance));
	auto removeFromFaction = annexerTag + " = {\n";
	removeFromFaction +=
		 "\t\t\tcountry_event = { "
		 "hours = 2 "
		 "id = NFEvents." +
		 std::to_string(nationalFocusEventNumber + 2) +
		 " "
		 "}\n";
	removeFromFaction += "\t\t\tif = {\n";
	removeFromFaction += "\t\t\t\tlimit = { is_in_faction_with = " + annexedTag + " }\n";
	removeFromFaction += "\t\t\t\tremove_from_faction = " + annexedTag + "\n";
	removeFromFaction += "\t\t\t}\n";
	removeFromFaction += "\t\t}";
	refuseOption.giveScriptBlock(std::move(removeFromFaction));
	sudetenEvent.giveOption(std::move(refuseOption));

	nationalFocusEvents.push_back(sudetenEvent);


	Event refusedEvent;
	refusedEvent.giveType("country_event");
	refusedEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber + 2));
	refusedEvent.giveTitle("\"[" + annexedTag + ".GetName] Refuses!\"");
	refusedEvent.giveDescription(
		 "= \"[" + annexedTag +
		 ".GetName] Refused our proposed proposition! This is an insult to us that cannot go unanswered!\"");
	refusedEvent.givePicture("GFX_report_event_german_troops");
	refusedEvent.setTriggeredOnly();

	EventOption refusedOption;
	refusedOption.giveName("\"It's time for war\"");
	std::string createWargoal = "create_wargoal = {\n";
	createWargoal += "\t\t\ttype = annex_everything\n";
	createWargoal += "\t\t\ttarget = " + annexedTag + "\n";
	createWargoal += "\t\t}";
	refusedOption.giveScriptBlock(std::move(createWargoal));
	refusedEvent.giveOption(std::move(refusedOption));

	nationalFocusEvents.push_back(refusedEvent);


	Event acceptedEvent;
	acceptedEvent.giveType("country_event");
	acceptedEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber + 1));
	acceptedEvent.giveTitle("\"[" + annexedTag + ".GetName] accepts!\"");
	acceptedEvent.giveDescription(
		 "= \"[" + annexedTag + ".GetName] accepted our proposed demands, the added lands will push us to greatness!\"");
	acceptedEvent.givePicture("GFX_report_event_german_speech");
	acceptedEvent.setTriggeredOnly();

	EventOption acceptedOption;
	acceptedOption.giveName("\"A stronger Union!\"");
	for (unsigned int i = 0; i <= 1 && i < claimedStates.size(); i++)
	{
		acceptedOption.giveScriptBlock(std::to_string(claimedStates[i]) + " = { add_core_of = " + annexerTag + " }");
		acceptedOption.giveScriptBlock(annexerTag + " = { transfer_state = " + std::to_string(claimedStates[i]) + " }");
	}
	acceptedOption.giveScriptBlock("set_country_flag = " + annexedTag + "_demanded");
	acceptedEvent.giveOption(std::move(acceptedOption));

	nationalFocusEvents.push_back(acceptedEvent);


	nationalFocusEventNumber += 3;
}


void HoI4::Events::createTradeEvent(const Country& leader, const std::string& aggressorTag)
{
	Event tradeIncidentEvent;
	tradeIncidentEvent.giveType("country_event");
	tradeIncidentEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber++));
	tradeIncidentEvent.giveTitle("\"Trade Incident\"");
	tradeIncidentEvent.giveDescription("= \"One of our convoys was sunk by [" + aggressorTag + ".GetName]\"");
	tradeIncidentEvent.givePicture("GFX_report_event_chinese_soldiers_fighting");
	tradeIncidentEvent.setTriggeredOnly();
	std::string trigger = "= {\n";
	trigger += "\t\thas_country_flag = established_traders\n";
	trigger += "\t\tNOT = { has_country_flag = established_traders_activated }\n";
	trigger += "\t}";
	tradeIncidentEvent.giveTrigger(std::move(trigger));

	EventOption option;
	option.giveName("\"They will Pay!\"");
	option.giveAiChance("= { factor = 85 }");
	std::string effectTooltip = "effect_tooltip = {\n";
	effectTooltip += "\t\t\t" + leader.getTag() + " = {\n";
	effectTooltip += "\t\t\t\tset_country_flag = established_traders_activated\n";
	effectTooltip += "\t\t\t\tcreate_wargoal = {\n";
	effectTooltip += "\t\t\t\t\ttype = annex_everything\n";
	effectTooltip += "\t\t\t\t\ttarget = " + aggressorTag + "\n";
	effectTooltip += "\t\t\t\t}\n";
	effectTooltip += "\t\t\t}\n";
	effectTooltip += "\t\t}";
	option.giveScriptBlock(std::move(effectTooltip));
	tradeIncidentEvent.giveOption(std::move(option));

	nationalFocusEvents.push_back(tradeIncidentEvent);
}


void HoI4::Events::createPoliticalEvents(const std::set<std::string>& majorIdeologies,
	 Localisation& localisation,
	 bool debug)
{
	Log(LogLevel::Info) << "\tCreating political events";

	addOnTheRise(majorIdeologies, localisation, debug);
	addMinisterRevolutionEvents(majorIdeologies, localisation, debug);
	addFiftyPercentEvents(majorIdeologies, localisation, debug);
	addRevolutionEvents(majorIdeologies, localisation, debug);
	addSuppressedEvents(majorIdeologies, localisation, debug);
}


void HoI4::Events::addOnTheRise(const std::set<std::string>& majorIdeologies, Localisation& localisation, bool debug)
{
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		Event onTheRise;
		onTheRise.giveType("country_event");
		onTheRise.giveId("conv.political." + std::to_string(politicalEventNumber));
		onTheRise.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations(ideology + "_on_the_rise.t", *onTheRise.getTitle(), debug);
		auto description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		onTheRise.giveDescription("= " + description);
		localisation.copyEventLocalisations(ideology + "_on_the_rise.d", description, debug);
		onTheRise.givePicture(getIdeologicalPicture(ideology));
		std::string addOnTheRiseTrigger = "= {\n";
		addOnTheRiseTrigger += "\t\tNOT = { has_government = " + ideology + " }\n";
		addOnTheRiseTrigger += "\t\t" + ideology + " > 0.6\n";
		addOnTheRiseTrigger += "\t\tNOT = { " + ideology + " > 0.7 }\n";
		addOnTheRiseTrigger += "\t}";
		onTheRise.giveTrigger(std::move(addOnTheRiseTrigger));
		onTheRise.setFireOnlyOnce();
		std::string onTheRiseMtth = "= {\n";
		onTheRiseMtth += "\t\tdays = 30\n";
		onTheRiseMtth += "\t}";
		onTheRise.giveMeanTimeToHappen(std::move(onTheRiseMtth));

		EventOption onTheRiseOptionA;
		auto optionAName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		localisation.copyEventLocalisations(ideology + "_on_the_rise.a", optionAName, debug);
		onTheRiseOptionA.giveName(std::move(optionAName));
		onTheRiseOptionA.giveScriptBlock("add_political_power = -100");
		std::string setPoliticsEffect = "set_politics = {\n";
		setPoliticsEffect += "\t\t\truling_party = " + ideology + "\n";
		setPoliticsEffect += "\t\t\telections_allowed = " + getElectionsAllowedString(ideology);
		setPoliticsEffect += "\t\t}";
		onTheRiseOptionA.giveScriptBlock(std::move(setPoliticsEffect));
		onTheRise.giveOption(std::move(onTheRiseOptionA));

		EventOption onTheRiseOptionB;
		auto optionBName = "conv.political." + std::to_string(politicalEventNumber) + ".b";
		localisation.copyEventLocalisations(ideology + "_on_the_rise.b", optionBName, debug);
		onTheRiseOptionB.giveName(std::move(optionBName));
		onTheRiseOptionB.giveAiChance("= {\n\t\t\tfactor = 0\n\t\t}");
		onTheRiseOptionB.giveScriptBlock("custom_effect_tooltip = impending_civil_war_tt");
		onTheRise.giveOption(std::move(onTheRiseOptionB));

		politicalEvents.push_back(onTheRise);
		politicalEventNumber++;
	}
}



void HoI4::Events::addMinisterRevolutionEvents(const std::set<std::string>& majorIdeologies,
	 Localisation& localisation,
	 bool debug)
{
	for (const auto& ideology: majorIdeologies)
	{
		if ((ideology == "neutrality") || (ideology == "democratic"))
		{
			continue;
		}

		Event addPopularity;
		addPopularity.giveType("country_event");
		addPopularity.giveId("conv.political." + std::to_string(politicalEventNumber));
		addPopularity.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations(ideology + "_add_popularity.t", *addPopularity.getTitle(), debug);
		auto description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		addPopularity.giveDescription("= " + description);
		localisation.copyEventLocalisations(ideology + "_add_popularity.d", description, debug);
		addPopularity.givePicture(getIdeologicalPicture(ideology));
		std::string addPopularityTrigger = "= {\n";
		addPopularityTrigger += "\t\thas_idea_with_trait = " + ideology + "_minister\n";
		addPopularityTrigger += "\t\tNOT = { has_government = " + ideology + " }\n";
		addPopularityTrigger += "\t\t" + ideology + " > 0.2\n";
		addPopularityTrigger += "\t\tNOT = { " + ideology + " > 0.59 }\n";
		addPopularityTrigger += "\t}";
		addPopularity.giveTrigger(std::move(addPopularityTrigger));
		std::string addPopularityMtth = "= {\n";
		addPopularityMtth += "\t\tdays = 365\n";
		addPopularityMtth += "\t\tmodifier = {\n";
		addPopularityMtth += "\t\t\tfactor = 0.5\n";
		addPopularityMtth += "\t\t\thas_country_flag = " + ideology + "_popular_movement\n";
		addPopularityMtth += "\t\t}\n";
		addPopularityMtth += "\t}";
		addPopularity.giveMeanTimeToHappen(std::move(addPopularityMtth));
		EventOption addPopularityOptionA;
		auto optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		localisation.copyEventLocalisations(ideology + "_add_popularity.a", optionName, debug);
		addPopularityOptionA.giveName(std::move(optionName));
		std::string addPopularityEffect = "add_popularity = {\n";
		addPopularityEffect += "\t\t\tideology = " + ideology + "\n";
		addPopularityEffect += "\t\t\tpopularity = 0.05\n";
		addPopularityEffect += "\t\t}";
		addPopularityOptionA.giveScriptBlock(std::move(addPopularityEffect));
		addPopularityOptionA.giveScriptBlock("add_stability = -0.05");
		addPopularity.giveOption(std::move(addPopularityOptionA));
		politicalEvents.push_back(addPopularity);
		politicalEventNumber++;

		Event militaryDefections;
		militaryDefections.giveType("country_event");
		militaryDefections.giveId("conv.political." + std::to_string(politicalEventNumber));
		militaryDefections.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations(ideology + "_military_defections.t", *militaryDefections.getTitle(), debug);
		auto description2 = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		militaryDefections.giveDescription("= " + description2);
		localisation.copyEventLocalisations(ideology + "_military_defections.d", description2, debug);
		militaryDefections.givePicture(getIdeologicalPicture(ideology));
		std::string militaryDefectionsTrigger = "= {\n";
		militaryDefectionsTrigger += "\t\thas_idea_with_trait = " + ideology + "_minister\n";
		militaryDefectionsTrigger += "\t\tNOT = { has_government = " + ideology + " }\n";
		militaryDefectionsTrigger += "\t\t" + ideology + " > 0.3\n";
		militaryDefectionsTrigger += "\t\tNOT = { " + ideology + " > 0.59 }\n";
		militaryDefectionsTrigger += "\t\tNOT = { has_idea = " + ideology + "_partisans_recruiting }\n";
		militaryDefectionsTrigger += "\t}";
		militaryDefections.giveTrigger(std::move(militaryDefectionsTrigger));
		std::string militaryDefectionsMtth = "= {\n";
		militaryDefectionsMtth += "\t\tdays = 365\n";
		militaryDefectionsMtth += "\t\tmodifier = {\n";
		militaryDefectionsMtth += "\t\t\tfactor = 0.5\n";
		militaryDefectionsMtth += "\t\t\thas_country_flag = " + ideology + "_popular_movement\n";
		militaryDefectionsMtth += "\t\t}\n";
		militaryDefectionsMtth += "\t}";
		militaryDefections.giveMeanTimeToHappen(std::move(militaryDefectionsMtth));
		EventOption militaryDefectionsOptionA;
		optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		localisation.copyEventLocalisations(ideology + "_military_defections.a", optionName, debug);
		militaryDefectionsOptionA.giveName(std::move(optionName));
		std::string militaryDefectionsAddPopularity = "add_popularity = {\n";
		militaryDefectionsAddPopularity += "\t\t\tideology = " + ideology + "\n";
		militaryDefectionsAddPopularity += "\t\t\tpopularity = 0.05\n";
		militaryDefectionsAddPopularity += "\t\t}";
		militaryDefectionsOptionA.giveScriptBlock(std::move(militaryDefectionsAddPopularity));
		militaryDefectionsOptionA.giveScriptBlock("add_ideas = " + ideology + "_partisans_recruiting");
		militaryDefections.giveOption(std::move(militaryDefectionsOptionA));
		politicalEvents.push_back(militaryDefections);
		politicalEventNumber++;
	}

	if (majorIdeologies.contains("democratic"))
	{
		addDemocraticMinisterRevolutionEvents(localisation, debug);
	}
}


void HoI4::Events::addDemocraticMinisterRevolutionEvents(Localisation& localisation, bool debug)
{
	Event opposition;
	opposition.giveType("country_event");
	opposition.giveId("conv.political." + std::to_string(politicalEventNumber));
	opposition.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
	localisation.copyEventLocalisations("democratic_opposition_forming.t", *opposition.getTitle(), debug);
	auto description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
	opposition.giveDescription("= " + description);
	localisation.copyEventLocalisations("democratic_opposition_forming.d", description, debug);
	opposition.givePicture(getIdeologicalPicture("democratic"));
	std::string oppositionTrigger = "= {\n";
	oppositionTrigger += "\t\thas_idea_with_trait = democratic_minister\n";
	oppositionTrigger += "\t\tNOT = { has_government = democratic }\n";
	oppositionTrigger += "\t\tNOT = { has_country_flag = democracy_opposition_formed }\n";
	oppositionTrigger += "\t\tis_puppet = no\n";
	oppositionTrigger += "\t\tNOT = { democratic > 0.59 }\n";
	oppositionTrigger += "\t}";
	opposition.giveTrigger(std::move(oppositionTrigger));
	std::string oppositionMtth = "= {\n";
	oppositionMtth += "\t\tdays = 300\n";
	oppositionMtth += "\t\tmodifier = {\n";
	oppositionMtth += "\t\t\tfactor = 0.5\n";
	oppositionMtth += "\t\t\thas_country_flag = democracy_popular_movement\n";
	oppositionMtth += "\t\t}\n";
	oppositionMtth += "\t}";
	opposition.giveMeanTimeToHappen(std::move(oppositionMtth));
	EventOption oppositionOptionA;
	auto optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
	localisation.copyEventLocalisations("democratic_opposition_forming.a", optionName, debug);
	oppositionOptionA.giveName(std::move(optionName));
	std::string addPopularity = "add_popularity = {\n";
	addPopularity += "\t\t\tideology = democratic\n";
	addPopularity += "\t\t\tpopularity = 0.05\n";
	addPopularity += "\t\t}";
	oppositionOptionA.giveScriptBlock(std::move(addPopularity));
	oppositionOptionA.giveScriptBlock("add_stability = -0.05");
	oppositionOptionA.giveScriptBlock("set_country_flag = democracy_opposition_formed");
	opposition.giveOption(std::move(oppositionOptionA));
	politicalEvents.push_back(opposition);
	politicalEventNumber++;

	Event callForElections;
	callForElections.giveType("country_event");
	callForElections.giveId("conv.political." + std::to_string(politicalEventNumber));
	callForElections.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
	localisation.copyEventLocalisations("democratic_call_for_elections.t", *callForElections.getTitle(), debug);
	auto description2 = "conv.political." + std::to_string(politicalEventNumber) + ".d";
	callForElections.giveDescription("= " + description2);
	localisation.copyEventLocalisations("democratic_call_for_elections.d", description2, debug);
	callForElections.givePicture(getIdeologicalPicture("democratic"));
	std::string callForElectionsTrigger = "= {\n";
	callForElectionsTrigger += "\t\thas_idea_with_trait = democratic_minister\n";
	callForElectionsTrigger += "\t\tNOT = { has_government = democratic }\n";
	callForElectionsTrigger += "\t\thas_country_flag = democracy_opposition_formed\n";
	callForElectionsTrigger += "\t\tNOT = { has_idea = democratic_opposition_voicing_protests }\n";
	callForElectionsTrigger += "\t}";
	callForElections.giveTrigger(std::move(callForElectionsTrigger));
	std::string callForElectionsMtth = "= {\n";
	callForElectionsMtth += "\t\tdays = 150\n";
	callForElectionsMtth += "\t}";
	callForElections.giveMeanTimeToHappen(std::move(callForElectionsMtth));
	EventOption callForElectionsOptionA;
	optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
	localisation.copyEventLocalisations("democratic_call_for_elections.a", optionName, debug);
	callForElectionsOptionA.giveName(std::move(optionName));
	callForElectionsOptionA.giveAiChance("= { base = 1 }");
	callForElections.giveOption(std::move(callForElectionsOptionA));
	EventOption callForElectionsOptionB;
	optionName = "conv.political." + std::to_string(politicalEventNumber) + ".b";
	localisation.copyEventLocalisations("democratic_call_for_elections.b", optionName, debug);
	callForElectionsOptionB.giveName(std::move(optionName));
	callForElectionsOptionB.giveAiChance("= { base = 1 }");
	callForElectionsOptionB.giveScriptBlock("add_political_power = -20");
	callForElectionsOptionB.giveScriptBlock("add_ideas = democratic_opposition_voicing_protests");
	callForElectionsOptionB.giveScriptBlock(
		 "add_timed_idea = { idea = democratic_opposition_voicing_protests days = 730 }");
	callForElections.giveOption(std::move(callForElectionsOptionB));
	politicalEvents.push_back(callForElections);
	politicalEventNumber++;
}


void HoI4::Events::addFiftyPercentEvents(const std::set<std::string>& majorIdeologies,
	 Localisation& localisation,
	 bool debug)
{
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		Event fiftyPercentEvent;
		fiftyPercentEvent.giveType("country_event");
		fiftyPercentEvent.giveId("conv.political." + std::to_string(politicalEventNumber));
		fiftyPercentEvent.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations(ideology + "_fifty_percent.t", *fiftyPercentEvent.getTitle(), debug);
		auto description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		fiftyPercentEvent.giveDescription("= " + description);
		localisation.copyEventLocalisations(ideology + "_fifty_percent.d", description, debug);
		fiftyPercentEvent.givePicture(getIdeologicalPicture(ideology));
		fiftyPercentEvent.setTriggeredOnly();
		EventOption optionC;
		auto optionName = "conv.political." + std::to_string(politicalEventNumber) + ".c";
		localisation.copyEventLocalisations(ideology + "_fifty_percent.c", optionName, debug);
		optionC.giveName(std::move(optionName));
		if (ideology == "democratic")
		{
			for (const auto& ideology2: majorIdeologies)
			{
				if ((ideology2 == "neutrality") || (ideology2 == "democratic"))
				{
					continue;
				}
				std::string timedIdeaScript = "if = {\n";
				timedIdeaScript += "\t\t\tlimit = { has_government = " + ideology2 + " }\n";
				timedIdeaScript += "\t\t\tadd_timed_idea = { idea = " + ideology2 + "_defeated days = 730 }\n";
				timedIdeaScript += "\t\t}";
				optionC.giveScriptBlock(std::move(timedIdeaScript));
			}
		}
		std::string setPoliticsScript = "set_politics = {\n";
		setPoliticsScript += "\t\t\truling_party = " + ideology + "\n";
		setPoliticsScript += "\t\t\telections_allowed = " + getElectionsAllowedString(ideology);
		setPoliticsScript += "\t\t}";
		optionC.giveScriptBlock(std::move(setPoliticsScript));
		if (ideology == "democratic")
		{
			optionC.giveScriptBlock("hold_election = ROOT");
		}
		optionC.giveScriptBlock("add_stability = -0.05");
		fiftyPercentEvent.giveOption(std::move(optionC));
		politicalEvents.push_back(fiftyPercentEvent);
		eventNumbers.insert(make_pair(std::string("fiftyPercent") + ideology, politicalEventNumber));
		politicalEventNumber++;
	}
}


void HoI4::Events::addRevolutionEvents(const std::set<std::string>& majorIdeologies,
	 Localisation& localisation,
	 bool debug)
{
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		Event revolutionEvent;
		revolutionEvent.giveType("country_event");
		revolutionEvent.giveId("conv.political." + std::to_string(politicalEventNumber));
		revolutionEvent.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations(ideology + "_revolution_event.t", *revolutionEvent.getTitle(), debug);
		auto description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		revolutionEvent.giveDescription("= " + description);
		localisation.copyEventLocalisations(ideology + "_revolution_event.d", description, debug);
		revolutionEvent.givePicture(getIdeologicalPicture(ideology));
		std::string trigger = "= {\n";
		trigger += "\t\t" + ideology + " > 0.7\n";
		trigger += "\t\tnum_of_controlled_states > 1\n";
		trigger += "\t\tNOT = { has_government = " + ideology + " }\n";
		trigger += "\t\thas_civil_war = no\n";
		trigger += "\t}";
		revolutionEvent.giveTrigger(std::move(trigger));

		std::string mtth = "= {\n";
		mtth += "\t\tdays = 2\n";
		mtth += "\t}";
		revolutionEvent.giveMeanTimeToHappen(std::move(mtth));
		std::string immediate = "= {\n";
		immediate += "\t\thidden_effect = { remove_ideas = " + ideology + "_revolutionaries }\n";
		immediate += "\t}";
		revolutionEvent.giveImmediate(std::move(immediate));
		EventOption optionA;
		auto optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		localisation.copyEventLocalisations(ideology + "_revolution_event.a", optionName, debug);
		optionA.giveName(std::move(optionName));
		std::string aiChanceA = "= {\n";
		aiChanceA += "\t\t\tfactor = 0\n";
		aiChanceA += "\t\t}";
		optionA.giveAiChance(std::move(aiChanceA));
		std::string startCivilWar = "start_civil_war = {\n";
		startCivilWar += "\t\t\tideology = " + ideology + "\n";
		startCivilWar += "\t\t\tsize = 0.5\n";
		startCivilWar += "\t\t}";
		optionA.giveScriptBlock(std::move(startCivilWar));
		revolutionEvent.giveOption(std::move(optionA));
		EventOption optionB;
		optionName = "conv.political." + std::to_string(politicalEventNumber) + ".b";
		localisation.copyEventLocalisations(ideology + "_revolution_event.b", optionName, debug);
		optionB.giveName(std::move(optionName));
		std::string aiChanceB = "ai_chance = {\n";
		aiChanceB += "\t\t\tfactor = 0\n";
		aiChanceB += "\t\t}";
		optionB.giveScriptBlock(std::move(aiChanceB));
		for (const auto& ideology2: majorIdeologies)
		{
			if (ideology2 == ideology)
			{
				continue;
			}
			std::string startCivilWar2 = "if = {\n";
			startCivilWar2 += "\t\t\tlimit = {\n";
			startCivilWar2 += "\t\t\t\thas_government = " + ideology2 + "\n";
			startCivilWar2 += "\t\t\t}\n";
			if ((ideology == "democratic") && (ideology2 != "neutrality"))
			{
				startCivilWar2 += "\t\t\tadd_timed_idea = { idea = " + ideology2 + "_defeated days = 730 }\n";
			}
			startCivilWar2 += "\t\t\tstart_civil_war = {\n";
			startCivilWar2 += "\t\t\t\truling_party = " + ideology + "\n";
			startCivilWar2 += "\t\t\t\tideology = " + ideology2 + "\n";
			startCivilWar2 += "\t\t\t\tsize = 0.5\n";
			startCivilWar2 += "\t\t\t}\n";
			if (ideology == "democratic")
			{
				startCivilWar2 += "\t\t\thold_election = ROOT\n";
			}
			startCivilWar2 += "\t\t}";
			optionB.giveScriptBlock(std::move(startCivilWar2));
		}
		revolutionEvent.giveOption(std::move(optionB));

		EventOption optionC;
		optionName = "conv.political." + std::to_string(politicalEventNumber) + ".c";
		// original versions have no localisations
		optionC.giveName(std::move(optionName));
		optionC.giveTrigger("is_ai = yes");
		optionC.giveScriptBlock("add_political_power = -100");
		std::string setPoliticsScript = "set_politics = {\n";
		setPoliticsScript += "\t\t\truling_party = " + ideology + "\n";
		setPoliticsScript += "\t\t\telections_allowed = " + getElectionsAllowedString(ideology);
		setPoliticsScript += "\t\t}";
		optionC.giveScriptBlock(std::move(setPoliticsScript));
		revolutionEvent.giveOption(std::move(optionC));

		politicalEvents.push_back(revolutionEvent);
		politicalEventNumber++;
	}
}


void HoI4::Events::addSuppressedEvents(const std::set<std::string>& majorIdeologies,
	 Localisation& localisation,
	 bool debug)
{
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		Event suppressedEvent;
		suppressedEvent.giveType("country_event");
		suppressedEvent.giveId("conv.political." + std::to_string(politicalEventNumber));
		suppressedEvent.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations(ideology + "_suppressed_event.t", *suppressedEvent.getTitle(), debug);
		auto description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		suppressedEvent.giveDescription("= " + description);
		localisation.copyEventLocalisations(ideology + "_suppressed_event.d", description, debug);
		suppressedEvent.givePicture(getIdeologicalPicture(ideology));
		std::string trigger = "= {\n";
		trigger += "\t\t" + ideology + " < 0.3\n";
		trigger += "\t\thas_idea = " + ideology + "_revolutionaries\n";
		trigger += "\t}";
		suppressedEvent.giveTrigger(std::move(trigger));
		std::string mtth = "= {\n";
		mtth += "\t\tdays = 2\n";
		mtth += "\t}";
		suppressedEvent.giveMeanTimeToHappen(std::move(mtth));
		EventOption option;
		auto optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		localisation.copyEventLocalisations(ideology + "_suppressed_event.a", optionName, debug);
		option.giveName(std::move(optionName));
		option.giveScriptBlock("remove_ideas = " + ideology + "_revolutionaries");
		suppressedEvent.giveOption(std::move(option));
		politicalEvents.push_back(suppressedEvent);
		politicalEventNumber++;
	}

	auto numRelevantIdeologies = 0;
	for (const auto& ideology: majorIdeologies)
	{
		if ((ideology == "democratic") || (ideology == "neutrality"))
		{
			continue;
		}
		numRelevantIdeologies++;
	}
	if (numRelevantIdeologies > 0)
	{
		Event removeNeutral;
		removeNeutral.giveType("country_event");
		removeNeutral.giveId("conv.political." + std::to_string(politicalEventNumber));
		removeNeutral.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		localisation.copyEventLocalisations("abandon_neutral.t", *removeNeutral.getTitle(), debug);
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology == "democratic") || (ideology == "neutrality"))
			{
				continue;
			}
			std::string description = "= {\n";
			description += "\t\ttext = political." + std::to_string(politicalEventNumber) + ".d_" + ideology + "\n";
			description += "\t\ttrigger = { has_government = " + ideology + " }\n";
			description += "\t}";
			removeNeutral.giveDescription(std::move(description));
			localisation.copyEventLocalisations("abandon_neutral.d_" + ideology,
				 "conv.political." + std::to_string(politicalEventNumber) + "_" + ideology,
				 debug);
		}
		removeNeutral.givePicture("GFX_report_event_journalists_speech");
		std::string trigger = "= {\n";
		trigger += "\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology == "democratic") || (ideology == "neutrality"))
			{
				continue;
			}
			trigger += "\t\t\thas_government = " + ideology + "\n";
		}
		trigger += "\t\t}\n";
		trigger += "\t\thas_idea = neutrality_idea\n";
		trigger += "\t}";
		removeNeutral.giveTrigger(std::move(trigger));
		std::string mtth = "= {\n";
		mtth += "\t\tdays = 2\n";
		mtth += "\t}";
		removeNeutral.giveMeanTimeToHappen(std::move(mtth));
		EventOption option;
		auto optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		localisation.copyEventLocalisations("abandon_neutral.a", optionName, debug);
		option.giveName(std::move(optionName));
		option.giveScriptBlock("remove_ideas = neutrality_idea");
		removeNeutral.giveOption(std::move(option));
		politicalEvents.push_back(removeNeutral);
	}
}


std::string HoI4::Events::getIdeologicalPicture(const std::string& ideology)
{
	if (ideology == "communism")
	{
		return "GFX_report_event_worker_protests";
	}
	if (ideology == "fascism")
	{
		return "GFX_report_event_fascist_gathering";
	}
	if (ideology == "democratic")
	{
		return "GFX_report_event_journalists_speech";
	}
	if (ideology == "radical")
	{
		return "GFX_report_event_gathering_protests";
	}
	if (ideology == "absolutist")
	{
		return "GFX_report_event_generic_factory";
	}

	return "GFX_report_event_gathering_protests";
}


void HoI4::Events::createWarJustificationEvents(const std::set<std::string>& majorIdeologies,
	 Localisation& localisation,
	 bool debug)
{
	Log(LogLevel::Info) << "\tCreating war justification events";

	auto eventNum = 21;
	for (const auto& majorIdeology: majorIdeologies)
	{
		for (const auto& majorIdeology2: majorIdeologies)
		{
			Event warJustification;
			warJustification.giveType("country_event");
			warJustification.giveId("war_justification." + std::to_string(eventNum));
			warJustification.giveTitle("war_justification." + std::to_string(eventNum) + ".t");
			warJustification.giveDescription("= war_justification." + std::to_string(eventNum) + ".d");
			warJustification.givePicture("GFX_report_event_iww_demonstration");
			warJustification.setTriggeredOnly();
			std::string trigger = "= {\n";
			trigger += "\t\thas_government = " + majorIdeology + "\n";
			trigger += "\t\tFROM = { has_government = " + majorIdeology2 + " }\n";
			trigger += "\t\tNOT = { has_country_flag = war_justification_last_event_political }\n";
			trigger += "\t}";
			warJustification.giveTrigger(std::move(trigger));
			EventOption option;
			option.giveName("war_justification." + std::to_string(eventNum) + ".a");
			option.giveScriptBlock(
				 "FROM = { country_event = { id = war_justification." + std::to_string(eventNum + 200) + " } }");
			option.giveScriptBlock("set_country_flag = war_justification_last_event_political");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_generic");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_neighbor");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_mobilized");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_borderthreat");
			warJustification.giveOption(std::move(option));
			warJustificationEvents.push_back(warJustification);
			localisation.copyEventLocalisations("war_justification." + majorIdeology + majorIdeology2 + ".t",
				 "war_justification." + std::to_string(eventNum) + ".t",
				 debug);
			localisation.copyEventLocalisations("war_justification." + majorIdeology + majorIdeology2 + ".d",
				 "war_justification." + std::to_string(eventNum) + ".d",
				 debug);
			localisation.copyEventLocalisations("war_justification." + majorIdeology + majorIdeology2 + ".a",
				 "war_justification." + std::to_string(eventNum) + ".a",
				 debug);

			Event warJustification2;
			warJustification2.giveType("country_event");
			warJustification2.giveId("war_justification." + std::to_string(200 + eventNum));
			warJustification2.giveTitle("war_justification." + std::to_string(200 + eventNum) + ".t");
			warJustification2.giveDescription("= war_justification." + std::to_string(200 + eventNum) + ".d");
			warJustification2.givePicture("GFX_report_event_iww_demonstration");
			warJustification2.setTriggeredOnly();
			EventOption option2;
			option2.giveName("war_justification." + std::to_string(200 + eventNum) + ".a");
			warJustification2.giveOption(std::move(option2));
			warJustificationEvents.push_back(warJustification2);
			localisation.copyEventLocalisations("war_justification." + majorIdeology + majorIdeology2 + "200.t",
				 "war_justification." + std::to_string(200 + eventNum) + ".t",
				 debug);
			localisation.copyEventLocalisations("war_justification." + majorIdeology + majorIdeology2 + "200.d",
				 "war_justification." + std::to_string(200 + eventNum) + ".d",
				 debug);
			localisation.copyEventLocalisations("war_justification." + majorIdeology + majorIdeology2 + "200.a",
				 "war_justification." + std::to_string(200 + eventNum) + ".a",
				 debug);

			eventNum++;
		}
	}

	Event warGoalExpired;
	warGoalExpired.giveType("country_event");
	warGoalExpired.giveId("war_justification.301");
	warGoalExpired.giveTitle("war_justification.301.t");
	warGoalExpired.giveDescription("= war_justification.301.d");
	warGoalExpired.givePicture("GFX_report_event_iww_demonstration");
	warGoalExpired.setTriggeredOnly();
	std::string trigger = "= {\n";
	trigger += "\t\thas_war = no\n";
	trigger += "\t}";
	warGoalExpired.giveTrigger(std::move(trigger));

	auto letter = 'a';
	for (const auto& ideology: majorIdeologies)
	{
		EventOption option;
		option.giveName("war_justification.301." + std::string(1, letter));
		option.giveScriptBlock("trigger = { has_government = " + ideology + " }");
		option.giveScriptBlock("add_political_power = -30");
		option.giveScriptBlock("add_war_support = -0.03");
		if (ideology != "neutrality")
		{
			std::string addPopularity = "add_popularity = {\n";
			addPopularity += "\t\t\tideology = " + ideology + "\n";
			addPopularity += "\t\t\tpopularity = -0.05\n";
			addPopularity += "\t\t}";
			option.giveScriptBlock(std::move(addPopularity));
		}
		warGoalExpired.giveOption(std::move(option));
		letter++;
	}
	warJustificationEvents.push_back(warGoalExpired);
}


void HoI4::Events::importElectionEvents(const std::set<std::string>& majorIdeologies, OnActions& onActions)
{
	Log(LogLevel::Info) << "\tImporting election events";

	registerKeyword("country_event", [this, majorIdeologies](const std::string& type, std::istream& theStream) {
		const Event electionEvent(type, theStream);
		if (majorIdeologies.contains("democratic") || (electionEvent.getId() != "election.3"))
		{
			electionEvents.push_back(electionEvent);
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("blankmod/events/ElectionEvents.txt");
	clearRegisteredKeywords();

	if (majorIdeologies.contains("democratic"))
	{
		onActions.addElectionEvent("election.3");
	}
	else
	{
		electionEvents.erase(std::remove_if(electionEvents.begin(),
										 electionEvents.end(),
										 [](Event& theEvent) {
											 return theEvent.getId() == "elections.3";
										 }),
			 electionEvents.end());
	}
}


constexpr int tagAndDashSize = 4;
void HoI4::Events::addPartyChoiceEvent(const std::string& countryTag,
	 const std::set<Vic2::Party>& parties,
	 OnActions& onActions,
	 const std::set<std::string>& majorIdeologies,
	 const Vic2::Localisations& vic2Localisations,
	 Localisation& hoi4Localisations,
	 bool debug)
{
	Event partyChoiceEvent;

	partyChoiceEvent.giveType("country_event");
	partyChoiceEvent.giveId("election." + std::to_string(electionEventNumber));
	partyChoiceEvent.giveTitle("election." + std::to_string(electionEventNumber) + ".t");
	hoi4Localisations.copyEventLocalisations("party_choice.t", *partyChoiceEvent.getTitle(), debug);
	auto description = "election." + std::to_string(electionEventNumber) + ".d";
	partyChoiceEvent.giveDescription("= " + description);
	hoi4Localisations.copyEventLocalisations("party_choice.d", description, debug);
	partyChoiceEvent.givePicture("GFX_report_event_usa_election_generic");
	partyChoiceEvent.setTriggeredOnly();
	std::string trigger = "= {\n";
	trigger += "\t\ttag = " + countryTag + "\n";
	if (majorIdeologies.contains("democratic"))
	{
		trigger += "\t\tOR = {\n";
		trigger += "\t\t\tdemocratic > 0.5\n";
		trigger += "\t\t\tneutrality > 0.5\n";
		trigger += "\t\t}\n";
	}
	else
	{
		trigger += "\t\tneutrality > 0.5\n";
	}
	trigger += "\t}";
	partyChoiceEvent.giveTrigger(std::move(trigger));

	auto optionLetter = 'a';
	for (const auto& party: parties)
	{
		if (party.getIdeology() == "conservative")
		{
			auto partyName = party.getName();
			auto trimmedName = partyName.substr(tagAndDashSize, partyName.size());

			auto optionName = "election." + std::to_string(electionEventNumber) + optionLetter;
			hoi4Localisations.addEventLocalisationFromVic2(partyName, optionName, vic2Localisations);
			EventOption option;
			option.giveName(std::move(optionName));
			if (majorIdeologies.contains("democratic"))
			{
				option.giveScriptBlock(
					 "set_party_name = { "
					 "ideology = democratic "
					 "long_name = " +
					 countryTag + "_" + trimmedName + "_party " + "name = " + countryTag + "_" + trimmedName +
					 "_party "
					 "}");
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = conservatism");
			}
			else
			{
				option.giveScriptBlock(
					 "set_party_name = { "
					 "ideology = neutrality "
					 "long_name = " +
					 countryTag + "_" + trimmedName + "_party " + "name = " + countryTag + "_" + trimmedName +
					 "_party "
					 "}");
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = conservatism_neutral");
			}
			partyChoiceEvent.giveOption(std::move(option));
			optionLetter++;
		}
		if (party.getIdeology() == "liberal")
		{
			auto partyName = party.getName();
			auto trimmedName = partyName.substr(tagAndDashSize, partyName.size());

			auto optionName = "election." + std::to_string(electionEventNumber) + optionLetter;
			EventOption option;
			hoi4Localisations.addEventLocalisationFromVic2(partyName, optionName, vic2Localisations);
			option.giveName(std::move(optionName));
			if (majorIdeologies.contains("democratic"))
			{
				option.giveScriptBlock(
					 "set_party_name = { "
					 "ideology = democratic "
					 "long_name = " +
					 countryTag + "_" + trimmedName + "_party " + "name = " + countryTag + "_" + trimmedName +
					 "_party "
					 "}");
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = liberalism");
			}
			else
			{
				option.giveScriptBlock(
					 "set_party_name = { "
					 "ideology = neutrality "
					 "long_name = " +
					 countryTag + "_" + trimmedName + "_party " + "name = " + countryTag + "_" + trimmedName +
					 "_party "
					 "}");
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = liberalism_neutral");
			}
			partyChoiceEvent.giveOption(std::move(option));
			optionLetter++;
		}
		if (party.getIdeology() == "socialist")
		{
			auto partyName = party.getName();
			auto trimmedName = partyName.substr(tagAndDashSize, partyName.size());

			auto optionName = "election." + std::to_string(electionEventNumber) + optionLetter;
			hoi4Localisations.addEventLocalisationFromVic2(partyName, optionName, vic2Localisations);
			EventOption option;
			option.giveName(std::move(optionName));
			if (majorIdeologies.contains("democratic"))
			{
				option.giveScriptBlock(
					 "set_party_name = { "
					 "ideology = democratic "
					 "long_name = " +
					 countryTag + "_" + trimmedName + "_party " + "name = " + countryTag + "_" + trimmedName +
					 "_party "
					 "}");
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = socialism");
			}
			else
			{
				option.giveScriptBlock(
					 "set_party_name = { "
					 "ideology = neutrality "
					 "long_name = " +
					 countryTag + "_" + trimmedName + "_party " + "name = " + countryTag + "_" + trimmedName +
					 "_party "
					 "}");
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = socialism_neutral");
			}
			partyChoiceEvent.giveOption(std::move(option));
			optionLetter++;
		}
	}
	// Fallback for utility tags, e.g. AAA - Observer
	if (optionLetter == 'a')
	{
		EventOption option;
		option.giveName("[Root.GetRulingPartyLong]");
		partyChoiceEvent.giveOption(std::move(option));
	}

	onActions.addElectionEvent(partyChoiceEvent.getId());
	electionEvents.push_back(partyChoiceEvent);
	electionEventNumber++;
}


void HoI4::Events::createStabilityEvents(const std::set<std::string>& majorIdeologies,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tCreating stability events";

	clearRegisteredKeywords();
	registerKeyword("add_namespace", commonItems::ignoreString);
	registerKeyword("country_event", [this](const std::string& type, std::istream& theStream) {
		Event newEvent(type, theStream);
		if (newEvent.getId().substr(0, 9) == "stability")
		{
			stabilityEvents.insert(make_pair(newEvent.getId(), newEvent));
		}
		else if (newEvent.getId().substr(0, 6) == "mutiny")
		{
			mutinyEvents.insert(make_pair(newEvent.getId(), newEvent));
		}
		else
		{
			strikesEvents.insert(make_pair(newEvent.getId(), newEvent));
		}
	});

	parseFile(theConfiguration.getHoI4Path() / "events/stability_events.txt");

	auto lowStabilitySelector = stabilityEvents.find("stability.3");
	std::stringstream trigger;
	trigger << "= {\n";
	trigger << "\t\thas_war = yes\n";
	trigger << "\t\thas_civil_war = no\n";
	trigger << "\t\tOR = {\n";
	trigger << "\t\t\thas_stability < 0.5\n";
	trigger << "\t\t\thas_war_support < 0.5\n";
	trigger << "\t\t}\n";
	trigger << "\t\tNOT = {\n";
	trigger << "\t\t\tAND = {\n";
	trigger << "\t\t\t\tis_major = yes\n";
	trigger << "\t\t\t\tall_enemy_country = {\n";
	trigger << "\t\t\t\t\tis_major = no\n";
	trigger << "\t\t\t\t}\n";
	trigger << "\t\t\t}\n";
	trigger << "\t\t}\n";
	trigger << "\t\tNOT = { \n";
	trigger << "\t\t\thas_country_flag = crisis_in_progress\n";
	trigger << "\t\t}\n";
	trigger << "\t\tNOT = { # Don't fire stability events if the country is not mobilising at all\n";
	trigger << "\t\t\tOR = {\n";
	trigger << "\t\t\t\thas_idea = disarmed_nation\n";
	trigger << "\t\t\t\thas_idea = volunteer_only\n";
	trigger << "\t\t\t}\n";
	trigger << "\t\t\tOR = {\n";
	trigger << "\t\t\t\thas_idea = undisturbed_isolation\n";
	trigger << "\t\t\t\thas_idea = isolation\n";
	trigger << "\t\t\t\thas_idea = civilian_economy\n";
	trigger << "\t\t\t}\n";
	trigger << "\t\t}\n";
	trigger << "\t}";
	lowStabilitySelector->second.giveTrigger(trigger.str());
	if (!majorIdeologies.contains("democratic"))
	{
		std::string mtth = "= {\n";
		mtth += "\t\tdays = 360\n";
		mtth += "\t\tmodifier = {\n";
		mtth += "\t\t\tfactor = 0.75\n";
		mtth += "\t\t\tOR = {\n";
		mtth += "\t\t\t\thas_stability < 0.4\n";
		mtth += "\t\t\t\thas_war_support < 0.4\n";
		mtth += "\t\t\t}\n";
		mtth += "\t\t}\n";
		mtth += "\t\tmodifier = {\n";
		mtth += "\t\t\tfactor = 0.75\n";
		mtth += "\t\t\tOR = {\n";
		mtth += "\t\t\t\thas_stability < 0.2\n";
		mtth += "\t\t\t\thas_war_support < 0.2\n";
		mtth += "\t\t\t}\n";
		mtth += "\t\t}\n";
		mtth += "\t}";
		lowStabilitySelector->second.giveMeanTimeToHappen(std::move(mtth));
	}

	std::stringstream immediate;
	immediate << "= { \n";
	immediate << "\t\trandom_list = {\n";
	immediate << "\t\t\t20 = { \n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0\n";
	immediate << "\t\t\t\t\thas_country_flag = draft_dodging_resolved\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0\n";
	immediate << "\t\t\t\t\thas_idea = disarmed_nation\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0\n";
	immediate << "\t\t\t\t\thas_idea = volunteer_only\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0.1\n";
	immediate << "\t\t\t\t\thas_war_support > 0.5\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tadd_ideas = draft_dodging \n";
	immediate << "\t\t\t\tcountry_event = stability.21\n";
	immediate << "\t\t\t} #draft dodging\n";
	immediate << "\t\t\t20 = { \n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0\n";
	immediate << "\t\t\t\t\thas_country_flag = strikes_resolved\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0.1\n";
	immediate << "\t\t\t\t\thas_stability > 0.5\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tadd_ideas = strikes_1 \n";
	immediate << "\t\t\t\tcountry_event = stability.22\n";
	immediate << "\t\t\t} #strikes\n";
	immediate << "\t\t\t20 = { \n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0\n";
	immediate << "\t\t\t\t\thas_country_flag = mutiny_resolved\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tmodifier = {\n";
	immediate << "\t\t\t\t\tfactor = 0.1\n";
	immediate << "\t\t\t\t\thas_war_support > 0.5\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t\tadd_ideas = mutiny_1 \n";
	immediate << "\t\t\t\tcountry_event = stability.23\n";
	immediate << "\t\t\t} #mutinies\n";
	immediate << "\t\t}\n";
	immediate << "\t\tif = {\n";
	immediate << "\t\t\tlimit = {\n";
	immediate << "\t\t\t\tNOT = {\n";
	immediate << "\t\t\t\t\thas_country_flag = crisis_in_progress\n";
	immediate << "\t\t\t\t}\n";
	immediate << "\t\t\t}\n";
	immediate << "\t\t\tset_country_flag = crisis_in_progress\n";
	immediate << "\t\t}\n";
	immediate << "\t}\n";
	lowStabilitySelector->second.giveImmediate(std::move(immediate.str()));

	auto conscriptionRebellion = stabilityEvents.find("stability.33");
	conscriptionRebellion->second.clearOptions();
	EventOption option;
	option.giveName("stability.33.a");
	std::string startExtremistCivilWar = "if = {\n";
	if (majorIdeologies.contains("democratic"))
	{
		startExtremistCivilWar += "\t\t\tlimit = { has_government = democratic }\n";
	}
	else
	{
		startExtremistCivilWar += "\t\t\tlimit = { has_government = neutrality }\n";
	}
	if (majorIdeologies.contains("communism"))
	{
		startExtremistCivilWar += "\t\t\tstart_civil_war = { ideology = communism size = 0.35 }\n";
	}
	else if (majorIdeologies.contains("radical"))
	{
		startExtremistCivilWar += "\t\t\tstart_civil_war = { ideology = radical size = 0.35 }\n";
	}
	else if (majorIdeologies.contains("fascism"))
	{
		startExtremistCivilWar += "\t\t\tstart_civil_war = { ideology = fascism size = 0.35 }\n";
	}
	else if (majorIdeologies.contains("absolutist"))
	{
		startExtremistCivilWar += "\t\t\tstart_civil_war = { ideology = absolutist size = 0.35 }\n";
	}
	startExtremistCivilWar += "\t\t}";
	option.giveScriptBlock(std::move(startExtremistCivilWar));
	if (majorIdeologies.contains("democratic"))
	{
		std::string startDemocraticCivilWar = "if = {\n";
		startDemocraticCivilWar += "\t\t\tlimit = {\n";
		startDemocraticCivilWar += "\t\t\t\tOR = {\n";
		for (const auto& majorIdeology: majorIdeologies)
		{
			if ((majorIdeology == "democratic") || (majorIdeology == "neutrality"))
			{
				continue;
			}

			startDemocraticCivilWar += "\t\t\t\t\thas_government = " + majorIdeology + "\n";
		}
		startDemocraticCivilWar += "\t\t\t\t}\n";
		startDemocraticCivilWar += "\t\t\t}\n";
		startDemocraticCivilWar += "\t\t\tstart_civil_war = { ideology = democratic size = 0.45 }\n";
		startDemocraticCivilWar += "\t\t}\n";
		option.giveScriptBlock(std::move(startDemocraticCivilWar));
	}
	option.giveScriptBlock("clr_country_flag = crisis_in_progress");
	option.giveScriptBlock("clr_country_flag = crisis_solution_in_progress");
	option.giveScriptBlock("set_country_flag = { flag = draft_dodging_resolved days = 90 }");
	conscriptionRebellion->second.giveOption(std::move(option));
}


std::optional<int> HoI4::Events::getEventNumber(const std::string& eventName) const
{
	if (const auto& eventRecord = eventNumbers.find(eventName); eventRecord != eventNumbers.end())
	{
		return eventRecord->second;
	}
	else
	{
		return std::nullopt;
	}
}


void HoI4::Events::generateGenericEvents(const Configuration& theConfiguration,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tCreating generic events";

	std::ifstream genericEventsFileStream(theConfiguration.getHoI4Path() / "events/Generic.txt");
	if (!genericEventsFileStream.is_open())
	{
		throw std::runtime_error("Could not open " + (theConfiguration.getHoI4Path() / "events/Generic.txt").string());
	}
	commonItems::absorbBOM(genericEventsFileStream);

	EventsFile genericEventsFile(genericEventsFileStream);
	genericEvents = genericEventsFile.takeEvents();

	genericEventsFileStream.close();

	for (auto& genericEvent: genericEvents)
	{
		if (genericEvent.getId() == "generic.1")
		{
			updateGenericEventOne(genericEvent);
		}
		else if (genericEvent.getId() == "generic.2")
		{
			updateGenericEventTwo(genericEvent, majorIdeologies);
		}
		else if (genericEvent.getId() == "generic.3")
		{
			updateGenericEventsThreeFourAndSix(genericEvent, 3, majorIdeologies);
		}
		else if (genericEvent.getId() == "generic.4")
		{
			updateGenericEventsThreeFourAndSix(genericEvent, 4, majorIdeologies);
		}
		else if (genericEvent.getId() == "generic.5")
		{
			updateGenericEventFive(genericEvent, majorIdeologies);
		}
		else if (genericEvent.getId() == "generic.6")
		{
			updateGenericEventsThreeFourAndSix(genericEvent, 3, majorIdeologies);
		}
		else if (genericEvent.getId() == "generic.7")
		{
			updateGenericEventSeven(genericEvent, majorIdeologies);
		}
		else if (genericEvent.getId() == "generic.14")
		{
			updateGenericEventFourteen(genericEvent, majorIdeologies);
		}
	}
}


void HoI4::Events::importCapitulationEvents(const Configuration& theConfiguration,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tImporting capitulation events";

	registerKeyword("news_event", [this](const std::string& type, std::istream& theStream) {
		const Event capitulationEvent(type, theStream);
		capitulationEvents.push_back(capitulationEvent);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(theConfiguration.getHoI4Path() / "events/CapitulationEvents.txt");
	clearRegisteredKeywords();

	updateCapitulationEvent(capitulationEvents[0], majorIdeologies);
}


void HoI4::Events::importMtgNavalTreatyEvents(const Configuration& theConfiguration,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tImporting naval treaty events";

	registerKeyword("country_event", [this](const std::string& type, std::istream& theStream) {
		const Event navalTreatyEvent(type, theStream);
		mtgNavalTreatyEvents.push_back(navalTreatyEvent);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(theConfiguration.getHoI4Path() / "events/MTG_naval_treaty_events.txt");
	clearRegisteredKeywords();

	for (auto& event: mtgNavalTreatyEvents)
	{
		if (event.getId() == "MTG_naval_treaty.1")
		{
			updateNavalTreatyEventOne(event, majorIdeologies);
		}
		else if (event.getId() == "MTG_naval_treaty.4")
		{
			updateNavalTreatyEventFour(event, majorIdeologies);
		}
		else if (event.getId() == "MTG_naval_treaty.6")
		{
			updateNavalTreatyEventSix(event, majorIdeologies);
		}
		else if (event.getId() == "MTG_naval_treaty.10")
		{
			updateNavalTreatyEventTen(event, majorIdeologies);
		}
	}
}


void HoI4::Events::importLarOccupationEvents(const Configuration& theConfiguration,
	 const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tImporting LAR_occupation events";

	registerKeyword("country_event", [this](const std::string& type, std::istream& theStream) {
		const Event occupationEvent(type, theStream);
		larOccupationEvents.push_back(occupationEvent);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile(theConfiguration.getHoI4Path() / "events/LAR_occupation.txt");
	clearRegisteredKeywords();

	for (auto& event: larOccupationEvents)
	{
		if (event.getId() == "occupied_countries.2")
		{
			updateCreateUprisingEvent(event, majorIdeologies);
		}
	}
}