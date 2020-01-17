#include "Events.h"
#include "../HoI4Country.h"
#include "../HoI4Faction.h"
#include "../HoI4Localisation.h"
#include "../OnActions.h"
#include "../../Configuration.h"
#include "../../V2World/Party.h"
#include "../../V2World/Country.h"
#include "Log.h"
#include "ParserHelpers.h"



void HoI4::Events::createFactionEvents(const HoI4::Country& leader, const HoI4::Country& newAlly)
{
	auto possibleleaderName = leader.getSourceCountry().getName("english");
	std::string leaderName;
	if (possibleleaderName)
	{
		leaderName = *possibleleaderName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine leader name for faction events";
		leaderName.clear();
	}

	auto possibleNewAllyName = newAlly.getSourceCountry().getName("english");
	std::string newAllyName;
	if (possibleNewAllyName)
	{
		newAllyName = *possibleNewAllyName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine new ally name for faction events";
		newAllyName = *possibleNewAllyName;
	}

	Event nfEvent;
	nfEvent.giveType("country_event");
	nfEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber++));
	nfEvent.giveTitle("\"Alliance Offer\"");
	nfEvent.giveDescription(
		"= \"We have been invited to an alliance with " + leaderName + ". Should we accept the invitation?\""
	);
	nfEvent.givePicture("news_event_generic_sign_treaty1");
	nfEvent.setTriggeredOnly();
	EventOption yesOption;
	yesOption.giveName("\"Yes\"");
	if (leader.isInFaction())
	{
		std::string allyStrategy = newAlly.getTag() + " = {\n";
		allyStrategy += "			add_ai_strategy = {\n";
		allyStrategy += "				type = alliance\n";
		allyStrategy += "				id = \"" + leader.getTag() + "\"\n";
		allyStrategy += "				value = 200\n";
		allyStrategy += "			}\n";
		allyStrategy += "			dismantle_faction = yes\n";
		allyStrategy += "		}";
		yesOption.giveScriptBlock(std::move(allyStrategy));
		std::string createFaction = "if = {\n";
		createFaction += "			limit = {\n";
		createFaction += "				" + leader.getTag() + " = {\n";
		createFaction += "					is_in_faction = no\n";
		createFaction += "				}\n";
		createFaction += "			}\n";
		createFaction += "			" + leader.getTag() + " = {\n";
		createFaction += "				create_faction = \"" + leaderName + "\"\n";
		createFaction += "			}\n";
		createFaction += "		}";
		yesOption.giveScriptBlock(std::move(createFaction));
		std::string addToFaction = leader.getTag() + " = {\n";
		addToFaction += "			add_to_faction = " + newAlly.getTag() + "\n";
		addToFaction += "		}";
		yesOption.giveScriptBlock(std::move(addToFaction));
	}
	yesOption.giveHiddenEffect("\t\t\tnews_event = { id = news." + to_string(newsEventNumber) + " }\n");
	nfEvent.giveOption(std::move(yesOption));
	EventOption noOption;
	noOption.giveName("\"No\"");
	noOption.giveAiChance("= { factor = 0 }");
	noOption.giveHiddenEffect("\t\t\tnews_event = { id = news." + to_string(newsEventNumber + 1) + " }\n");
	nfEvent.giveOption(std::move(noOption));
	nationalFocusEvents.push_back(nfEvent);

	Event newsEventYes;
	newsEventYes.giveType("news_event");
	newsEventYes.giveId("news." + to_string(newsEventNumber));
	newsEventYes.giveTitle("\"" + newAllyName + " formalizes alliance with " + leaderName + "\"");
	newsEventYes.giveDescription(
		"= \"The leaders of both countries have announced their intent of military cooperation.\""
	);
	newsEventYes.givePicture("news_event_generic_sign_treaty1");
	newsEventYes.setMajor();
	newsEventYes.setTriggeredOnly();
	EventOption interestingOption;
	interestingOption.giveName("\"Interesting\"");
	newsEventYes.giveOption(std::move(interestingOption));
	newsEvents.push_back(newsEventYes);

	Event newsEventNo;
	newsEventNo.giveType("news_event");
	newsEventNo.giveId("news." + to_string(newsEventNumber + 1));
	newsEventNo.giveTitle("\"" + newAllyName + " refuses the alliance offer of " + leaderName + "\"");
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


void HoI4::Events::createAnnexEvent(const HoI4::Country& annexer, const HoI4::Country& annexed)
{
	auto possibleannexerName = annexer.getSourceCountry().getName("english");
	std::string annexerName;
	if (possibleannexerName)
	{
		annexerName = *possibleannexerName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexer name for annexation events";
		annexerName.clear();
	}

	auto possibleannexedName = annexed.getSourceCountry().getName("english");
	std::string annexedName;
	if (possibleannexedName)
	{
		annexedName = *possibleannexedName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexed country name for annexation events";
		annexedName.clear();
	}

	Event annexEvent;
	annexEvent.giveType("country_event");
	annexEvent.giveId("NFEvents." + to_string(nationalFocusEventNumber));
	annexEvent.giveTitle("\"" + annexerName + " Demands " + annexedName + "!\"");
	std::string description = "= \"Today " + annexerName + " sent an envoy to us with a proposition of an union. ";
	description += "We are alone and in this world, and a union with " + annexerName + " might prove to be fruiteful. ";
	description += "Our people would be safe with the mighty army of " + annexerName + 
		" and we could possibly flourish with their established economy. ";
	description += "Or we could refuse the union which would surely lead to war, but maybe we can hold them off!\"";
	annexEvent.giveDescription(std::move(description));
	annexEvent.givePicture("GFX_report_event_hitler_parade");
	annexEvent.setTriggeredOnly();

	EventOption acceptOption;
	acceptOption.giveName("We accept the Union");
	std::string acceptAiChance = "\n";
	acceptAiChance += "			base = 30\n";
	acceptAiChance += "			modifier = {\n";
	acceptAiChance += "				add = -15\n";
	acceptAiChance += "				" + annexed.getTag() + " = { has_army_size = { size < 40 } }\n";
	acceptAiChance += "			}\n";
	acceptAiChance += "			modifier = {\n";
	acceptAiChance += "				add = 45\n";
	acceptAiChance += "				" + annexed.getTag() + " = { has_army_size = { size > 39 } }\n";
	acceptAiChance += "			}\n";
	acceptOption.giveAiChance(std::move(acceptAiChance));
	std::string acceptNewsEvent = "		" + annexed.getTag() + " = {\n";
	acceptNewsEvent += "			country_event = { " \
			"hours = 2 " \
			"id = NFEvents." + std::to_string(nationalFocusEventNumber + 1) + " " \
		"}\n";
	acceptNewsEvent += "		}\n";
	acceptNewsEvent += "		custom_effect_tooltip = GAME_OVER_TT\n";
	acceptNewsEvent += "	}";
	acceptOption.giveScriptBlock(std::move(acceptNewsEvent));
	annexEvent.giveOption(std::move(acceptOption));

	EventOption refuseOption;
	refuseOption.giveName("We Refuse!");
	std::string refuseAiChance = "n";
	refuseAiChance += "			base = 10\n";
	refuseAiChance += "\n";
	refuseAiChance += "			modifier = {\n";
	refuseAiChance += "				factor = 0\n";
	refuseAiChance += "				" + annexed.getTag() + " = { has_army_size = { size > 39 } }\n";
	refuseAiChance += "			}\n";
	refuseAiChance += "			modifier = {\n";
	refuseAiChance += "				add = 20\n";
	refuseAiChance += "				" + annexed.getTag() + " = { has_army_size = { size < 30 } }\n";
	refuseAiChance += "			}\n";
	refuseAiChance += "\t\t";
	acceptOption.giveAiChance(std::move(refuseAiChance));
	std::string removeFromFaction = "		" + annexed.getTag() + " = {\n";
	removeFromFaction += "			country_event = { " \
			"hours = 2 " \
			"id = NFEvents." + std::to_string(nationalFocusEventNumber + 2) + " " \
		"}\n";
	removeFromFaction += "			if = {\n";
	removeFromFaction += "				limit = { is_in_faction_with = " + annexed.getTag() + " }\n";
	removeFromFaction += "				remove_from_faction = " + annexed.getTag() + "\n";
	removeFromFaction += "			}\n";
	removeFromFaction += "		}\n";
	removeFromFaction += "	}";
	refuseOption.giveScriptBlock(std::move(removeFromFaction));
	annexEvent.giveOption(std::move(refuseOption));

	nationalFocusEvents.push_back(annexEvent);


	Event refusedEvent;
	refusedEvent.giveType("country_event");
	refusedEvent.giveId("NFEvents." + to_string(nationalFocusEventNumber + 2));
	refusedEvent.giveTitle("\"" + annexedName + " Refuses!\"");
	refusedEvent.giveDescription(
		"= \"" + annexedName + " Refused our proposed union! This is an insult to us that cannot go unanswered!\""
	);
	refusedEvent.givePicture("GFX_report_event_german_troops");
	refusedEvent.setTriggeredOnly();

	EventOption refusedOption;
	refusedOption.giveName("\"It's time for war\"");
	std::string wargoal = "create_wargoal = {\n";
	wargoal += "			type = annex_everything\n";
	wargoal += "			target = " + annexed.getTag() + "\n";
	wargoal += "		}\n";
	wargoal += "	}";
	refusedOption.giveScriptBlock(std::move(wargoal));
	refusedEvent.giveOption(std::move(refusedOption));

	nationalFocusEvents.push_back(refusedEvent);


	Event acceptedEvent;
	acceptedEvent.giveType("country_event");
	acceptedEvent.giveId("NFEvents." + to_string(nationalFocusEventNumber + 1));
	acceptedEvent.giveTitle("\"" + annexedName + " accepts!\"");
	acceptedEvent.giveDescription(
		"= \"" + annexedName + " accepted our proposed union, their added strength will push us to greatness!\""
	);
	acceptedEvent.givePicture("GFX_report_event_german_speech");
	acceptedEvent.setTriggeredOnly();

	EventOption acceptedOption;
	acceptedOption.giveName("\"A stronger Union!\"");
	for (auto state: annexed.getStates())
	{
		std::string addCore = "		" + to_string(state) + " = {\n";
		addCore += "			if = {\n";
		addCore += "				limit = { is_owned_by = " + annexed.getTag() + " }\n";
		addCore += "				add_core_of = " + annexed.getTag() + "\n";
		addCore += "			}\n";
		addCore += "		}";
		acceptedOption.giveScriptBlock(std::move(addCore));
	}
	acceptedOption.giveScriptBlock("		annex_country = { target = " + annexed.getTag() + " transfer_troops = yes }");
	acceptedOption.giveScriptBlock("		add_political_power = 50");
	acceptedOption.giveScriptBlock(
		"		add_named_threat = { threat = 2 name = \"" + annexerName + " annexed " + annexedName + "\" }"
	);
	acceptedOption.giveScriptBlock("		set_country_flag = " + annexed.getTag() + "_annexed");
	acceptedEvent.giveOption(std::move(acceptedOption));

	nationalFocusEvents.push_back(acceptedEvent);


	nationalFocusEventNumber += 3;
}


void HoI4::Events::createSudetenEvent(
	const HoI4::Country& annexer,
	const HoI4::Country& annexed,
	const std::vector<int>& claimedStates
)
{
	auto possibleannexerName = annexer.getSourceCountry().getName("english");
	std::string annexerName;
	if (possibleannexerName)
	{
		annexerName = *possibleannexerName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexer name for sudeten events";
		annexerName.clear();
	}

	auto possibleannexerAdjective = annexer.getSourceCountry().getName("english");
	std::string annexerAdjctive;
	if (possibleannexerAdjective)
	{
		annexerAdjctive = *possibleannexerAdjective;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexer adjective for sudeten events";
		annexerAdjctive.clear();
	}

	auto possibleannexedName = annexed.getSourceCountry().getName("english");
	std::string annexedName;
	if (possibleannexedName)
	{
		annexedName = *possibleannexedName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine annexed country name for sudeten events";
		annexedName.clear();
	}

	Event sudetenEvent;
	sudetenEvent.giveType("country_event");
	sudetenEvent.giveId("NFEvents." + to_string(nationalFocusEventNumber));
	sudetenEvent.giveTitle(annexerName + " Demands " + annexedName + "!");
	std::string description = "= \"" + annexerName + " has recently been making claims to our bordering states, ";
	description += "saying that these states are full of " + annexerAdjctive + 
		" people and that the territory should be given to them. ";
	description += "Although it is true that recently our neighboring states have had an influx of " + annexerAdjctive + 
		" people in the recent years, ";
	description += "we cannot give up our lands because a few " + annexerAdjctive + " settled down in our land. ";
	description += "In response " + annexerName + 
		" has called for a conference, demanding their territory in exchange for peace. How do we respond? ";
	description += "Our people would be safe with the mighty army of " + annexerName + 
		" and we could possibly flourish with their established economy. ";
	description += "Or we could refuse the union which would surely lead to war, but maybe we can hold them off!\"";
	sudetenEvent.giveDescription(std::move(description));
	sudetenEvent.givePicture("GFX_report_event_hitler_parade");
	sudetenEvent.setTriggeredOnly();

	EventOption acceptOption;
	acceptOption.giveName("\"We Accept\"");
	std::string acceptAiChance = " = {\n";
	acceptAiChance += "			base = 30\n";
	acceptAiChance += "			modifier = {\n";
	acceptAiChance += "				add = -15\n";
	acceptAiChance += "				" + annexer.getTag() + " = { has_army_size = { size < 40 } }\n";
	acceptAiChance += "			}\n";
	acceptAiChance += "			modifier = {\n";
	acceptAiChance += "				add = 45\n";
	acceptAiChance += "				" + annexer.getTag() + " = { has_army_size = { size > 39 } }\n";
	acceptAiChance += "			}\n";
	acceptAiChance += "		}";
	acceptOption.giveAiChance(std::move(acceptAiChance));
	std::string acceptNewsEvent = "		" + annexer.getTag() + " = {\n";
	acceptNewsEvent += "			country_event = { " \
			"hours = 2 " \
			"id = NFEvents." + to_string(nationalFocusEventNumber + 1) + " " \
		"}\n";
	acceptNewsEvent += "		}\n";
	acceptNewsEvent += "	}";
	acceptOption.giveScriptBlock(std::move(acceptNewsEvent));
	sudetenEvent.giveOption(std::move(acceptOption));

	EventOption refuseOption;
	refuseOption.giveName("\"We Refuse!\"");
	std::string refuseAiChance = " = {\n";
	refuseAiChance += "			base = 10\n";
	refuseAiChance += "\n";
	refuseAiChance += "			modifier = {\n";
	refuseAiChance += "				factor = 0\n";
	refuseAiChance += "				" + annexer.getTag() + " = { has_army_size = { size > 39 } }\n";
	refuseAiChance += "			}\n";
	refuseAiChance += "			modifier = {\n";
	refuseAiChance += "				add = 20\n";
	refuseAiChance += "				" + annexer.getTag() + " = { has_army_size = { size < 30 } }\n";
	refuseAiChance += "			}\n";
	refuseAiChance += "		}";
	refuseOption.giveAiChance(std::move(refuseAiChance));
	std::string removeFromFaction = annexer.getTag() + " = {\n";
	removeFromFaction += "			country_event = { " \
			"hours = 2 " \
			"id = NFEvents." + std::to_string(nationalFocusEventNumber + 2) + " " \
		"}\n";
	removeFromFaction += "			if = {\n";
	removeFromFaction += "				limit = { is_in_faction_with = " + annexed.getTag() + " }\n";
	removeFromFaction += "				remove_from_faction = " + annexed.getTag() + "\n";
	removeFromFaction += "			}\n";
	removeFromFaction += "		}\n";
	removeFromFaction += "	}";
	refuseOption.giveScriptBlock(std::move(removeFromFaction));
	sudetenEvent.giveOption(std::move(refuseOption));

	nationalFocusEvents.push_back(sudetenEvent);


	Event refusedEvent;
	refusedEvent.giveType("country_event");
	refusedEvent.giveId("NFEvents." + to_string(nationalFocusEventNumber + 2));
	refusedEvent.giveTitle("\"" + annexedName + " Refuses!\"");
	refusedEvent.giveDescription(
		"= \"" + annexedName + " Refused our proposed proposition! This is an insult to us that cannot go unanswered!\""
	);
	refusedEvent.givePicture("GFX_report_event_german_troops");
	refusedEvent.setTriggeredOnly();

	EventOption refusedOption;
	refusedOption.giveName("\"It's time for war\"");
	std::string createWargoal = "create_wargoal = {\n";
	createWargoal += "				type = annex_everything\n";
	createWargoal += "			target = " + annexed.getTag() + "\n";
	createWargoal += "		}\n";
	createWargoal += "	}";
	refusedOption.giveScriptBlock(std::move(createWargoal));
	refusedEvent.giveOption(std::move(refusedOption));

	nationalFocusEvents.push_back(refusedEvent);


	Event acceptedEvent;
	acceptedEvent.giveType("country_event");
	acceptedEvent.giveId("NFEvents." + to_string(nationalFocusEventNumber + 1));
	acceptedEvent.giveTitle("\"" + annexedName + " accepts!\"");
	acceptedEvent.giveDescription(
		"= \"" + annexedName + " accepted our proposed demands, the added lands will push us to greatness!\""
	);
	acceptedEvent.givePicture("GFX_report_event_german_speech");
	acceptedEvent.setTriggeredOnly();

	EventOption acceptedOption;
	acceptedOption.giveName("\"A stronger Union!\"");
	for (unsigned int i = 0; i <= 1 && i < claimedStates.size(); i++)
	{
		acceptedOption.giveScriptBlock(to_string(claimedStates[i]) + " = { add_core_of = " + annexer.getTag() + " }");
		acceptedOption.giveScriptBlock(
			annexer.getTag() + " = { transfer_state =  " + to_string(claimedStates[i]) + " }"
		);
	}
	acceptedOption.giveScriptBlock("set_country_flag = " + annexed.getTag() + "_demanded");
	acceptedEvent.giveOption(std::move(acceptedOption));

	nationalFocusEvents.push_back(acceptedEvent);


	nationalFocusEventNumber += 3;
}


void HoI4::Events::createTradeEvent(const HoI4::Country& leader, const HoI4::Country& greatPower)
{
	auto possibleAggressorName = greatPower.getSourceCountry().getName("english");
	std::string aggressorName;
	if (possibleAggressorName)
	{
		aggressorName = *possibleAggressorName;
	}
	else
	{
		Log(LogLevel::Warning) << "Could not determine aggressor name for trade events";
		aggressorName.clear();
	}

	Event tradeIncidentEvent;
	tradeIncidentEvent.giveType("country_event");
	tradeIncidentEvent.giveId("NFEvents." + std::to_string(nationalFocusEventNumber++));
	tradeIncidentEvent.giveTitle("\"Trade Incident\"");
	tradeIncidentEvent.giveDescription("= \"One of our convoys was sunk by " + aggressorName + "\"");
	tradeIncidentEvent.givePicture("GFX_report_event_chinese_soldiers_fighting");
	tradeIncidentEvent.setTriggeredOnly();
	std::string trigger = "= {\n";
	trigger += "		has_country_flag = established_traders\n";
	trigger += "		NOT = { has_country_flag = established_traders_activated }\n";
	trigger += "	}";
	tradeIncidentEvent.giveTrigger(std::move(trigger));

	EventOption option;
	option.giveName("\"They will Pay!\"");
	option.giveAiChance("= { factor = 85 }");
	std::string effectTooltip = "effect_tooltip = {\n";
	effectTooltip += "			" + leader.getTag() + " = {\n";
	effectTooltip += "				set_country_flag = established_traders_activated\n";
	effectTooltip += "				create_wargoal = {\n";
	effectTooltip += "					type = annex_everything\n";
	effectTooltip += "					target = " + greatPower.getTag() + "\n";
	effectTooltip += "				}\n";
	effectTooltip += "			}\n";
	effectTooltip += "		}";
	option.giveScriptBlock(std::move(effectTooltip));
	tradeIncidentEvent.giveOption(std::move(option));

	nationalFocusEvents.push_back(tradeIncidentEvent);
}


void HoI4::Events::createPoliticalEvents(const std::set<std::string>& majorIdeologies)
{
	addMinisterRevolutionEvents(majorIdeologies);
	addFiftyPercentEvents(majorIdeologies);
	addRevolutionEvents(majorIdeologies);
	addSuppressedEvents(majorIdeologies);
}


void HoI4::Events::addMinisterRevolutionEvents(const std::set<std::string>& majorIdeologies)
{
	for (auto ideology: majorIdeologies)
	{
		if ((ideology == "neutrality") || (ideology == "democratic"))
		{
			continue;
		}

		Event addPopularity;
		addPopularity.giveType("country_event");
		addPopularity.giveId("conv.political." + std::to_string(politicalEventNumber));
		addPopularity.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		HoI4Localisation::copyEventLocalisations(ideology + "_add_popularity.t", addPopularity.getTitle());
		std::string description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		addPopularity.giveDescription("= " + description);
		HoI4Localisation::copyEventLocalisations(ideology + "_add_popularity.d", description);
		addPopularity.givePicture(getIdeologicalPicture(ideology));
		std::string addPopularityTrigger = "= {\n";
		addPopularityTrigger += "		has_idea_with_trait = " + ideology + "_minister\n";
		addPopularityTrigger += "		NOT = { has_government = " + ideology + " }\n";
		addPopularityTrigger += "		" + ideology + " > 0.2\n";
		addPopularityTrigger += "	}";
		addPopularity.giveTrigger(std::move(addPopularityTrigger));
		std::string addPopularityMtth = "= {\n";
		addPopularityMtth += "		days = 365\n";
		addPopularityMtth += "		modifier = {\n";
		addPopularityMtth += "			factor = 0.5\n";
		addPopularityMtth += "			has_country_flag = " + ideology + "_popular_movement\n";
		addPopularityMtth += "		}\n";
		addPopularityMtth += "	}";
		addPopularity.giveMeanTimeToHappen(std::move(addPopularityMtth));
		EventOption addPopularityOptionA;
		std::string optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		HoI4Localisation::copyEventLocalisations(ideology + "_add_popularity.a", optionName);
		addPopularityOptionA.giveName(std::move(optionName));
		std::string addPopularityEffect = "add_popularity = {\n";
		addPopularityEffect += "			ideology = " + ideology + "\n";
		addPopularityEffect += "			popularity = 0.05\n";
		addPopularityEffect += "		}";
		addPopularityOptionA.giveScriptBlock(std::move(addPopularityEffect));
		addPopularityOptionA.giveScriptBlock("add_stability = -0.05");
		addPopularity.giveOption(std::move(addPopularityOptionA));
		politicalEvents.push_back(addPopularity);
		politicalEventNumber++;

		Event militaryDefections;
		militaryDefections.giveType("country_event");
		militaryDefections.giveId("conv.political." + std::to_string(politicalEventNumber));
		militaryDefections.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		HoI4Localisation::copyEventLocalisations(ideology + "_military_defections.t", militaryDefections.getTitle());
		std::string description2 = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		militaryDefections.giveDescription("= " + description2);
		HoI4Localisation::copyEventLocalisations(ideology + "_military_defections.d", description2);
		militaryDefections.givePicture(getIdeologicalPicture(ideology));
		std::string militaryDefectionsTrigger = "= {\n";
		militaryDefectionsTrigger += "		has_idea_with_trait = " + ideology + "_minister\n";
		militaryDefectionsTrigger += "		NOT = { has_government = " + ideology + " }\n";
		militaryDefectionsTrigger += "		" + ideology + " > 0.3\n";
		militaryDefectionsTrigger += "		NOT = { has_idea = " + ideology + "_partisans_recruiting }\n";
		militaryDefectionsTrigger += "	}";
		militaryDefections.giveTrigger(std::move(militaryDefectionsTrigger));
		std::string militaryDefectionsMtth = "= {\n";
		militaryDefectionsMtth += "		days = 365\n";
		militaryDefectionsMtth += "		modifier = {\n";
		militaryDefectionsMtth += "			factor = 0.5\n";
		militaryDefectionsMtth += "			has_country_flag = " + ideology + "_popular_movement\n";
		militaryDefectionsMtth += "		}\n";
		militaryDefectionsMtth += "	}";
		militaryDefections.giveMeanTimeToHappen(std::move(militaryDefectionsMtth));
		EventOption militaryDefectionsOptionA;
		optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		HoI4Localisation::copyEventLocalisations(ideology + "_military_defections.a", optionName);
		militaryDefectionsOptionA.giveName(std::move(optionName));
		std::string militaryDefectionsAddPopularity = "add_popularity = {\n";
		militaryDefectionsAddPopularity += "			ideology = " + ideology + "\n";
		militaryDefectionsAddPopularity += "			popularity = 0.05\n";
		militaryDefectionsAddPopularity += "		}";
		militaryDefectionsOptionA.giveScriptBlock(std::move(militaryDefectionsAddPopularity));
		militaryDefectionsOptionA.giveScriptBlock("add_ideas = " + ideology + "_partisans_recruiting");
		militaryDefections.giveOption(std::move(militaryDefectionsOptionA));
		politicalEvents.push_back(militaryDefections);
		politicalEventNumber++;
	}

	if (majorIdeologies.count("democratic") > 0)
	{
		addDemocraticMinisterRevolutionEvents(majorIdeologies);
	}
}


void HoI4::Events::addDemocraticMinisterRevolutionEvents(const std::set<std::string>& majorIdeologies)
{
	Event opposition;
	opposition.giveType("country_event");
	opposition.giveId("conv.political." + std::to_string(politicalEventNumber));
	opposition.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
	HoI4Localisation::copyEventLocalisations("democratic_opposition_forming.t", opposition.getTitle());
	std::string description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
	opposition.giveDescription("= " + description);
	HoI4Localisation::copyEventLocalisations("democratic_opposition_forming.d", description);
	opposition.givePicture(getIdeologicalPicture("democratic"));
	std::string oppositionTrigger = "= {\n";
	oppositionTrigger += "		has_idea_with_trait = democratic_reformer\n";
	oppositionTrigger += "		NOT = { has_government = democratic }\n";
	oppositionTrigger += "		NOT = { has_country_flag = democracy_opposition_formed }\n";
	oppositionTrigger += "		is_puppet = no\n";
	oppositionTrigger += "	}";
	opposition.giveTrigger(std::move(oppositionTrigger));
	std::string oppositionMtth = "= {\n";
	oppositionMtth += "		days = 300\n";
	oppositionMtth += "		modifier = {\n";
	oppositionMtth += "			factor = 0.5\n";
	oppositionMtth += "			has_country_flag = democracy_popular_movement\n";
	oppositionMtth += "		}\n";
	oppositionMtth += "	}";
	opposition.giveMeanTimeToHappen(std::move(oppositionMtth));
	EventOption oppositionOptionA;
	std::string optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
	HoI4Localisation::copyEventLocalisations("democratic_opposition_forming.a", optionName);
	oppositionOptionA.giveName(std::move(optionName));
	std::string addPopularity = "add_popularity = {\n";
	addPopularity += "			ideology = democratic\n";
	addPopularity += "			popularity = 0.05\n";
	addPopularity += "		}";
	oppositionOptionA.giveScriptBlock(std::move(addPopularity));
	oppositionOptionA.giveScriptBlock("add_stability = -0.05");
	oppositionOptionA.giveScriptBlock("set_country_flag = democracy_opposition_formed");
	opposition.giveOption(std::move(oppositionOptionA));
	politicalEvents.push_back(opposition);
	politicalEventNumber++;

	Event callForElections;
	callForElections.giveType("country_event");
	callForElections.giveId("conv.political." + std::to_string(politicalEventNumber));
	callForElections.giveTitle("conv.political." + to_string(politicalEventNumber) + ".t");
	HoI4Localisation::copyEventLocalisations("democratic_call_for_elections.t", callForElections.getTitle());
	std::string description2 = "conv.political." + to_string(politicalEventNumber) + ".d";
	callForElections.giveDescription("= " + description2);
	HoI4Localisation::copyEventLocalisations("democratic_call_for_elections.d", description2);
	callForElections.givePicture(getIdeologicalPicture("democratic"));
	std::string callForElectionsTrigger = "= {\n";
	callForElectionsTrigger += "		has_idea_with_trait = democratic_reformer\n";
	callForElectionsTrigger += "		NOT = { has_government = democratic }\n";
	callForElectionsTrigger += "		has_country_flag = democracy_opposition_formed\n";
	callForElectionsTrigger += "		NOT = { has_idea = democratic_opposition_voicing_protests }\n";
	callForElectionsTrigger += "	}";
	callForElections.giveTrigger(std::move(callForElectionsTrigger));
	std::string callForElectionsMtth = "= {\n";
	callForElectionsMtth += "		days = 150\n";
	callForElectionsMtth += "	}";
	callForElections.giveMeanTimeToHappen(std::move(callForElectionsMtth));
	EventOption callForElectionsOptionA;
	optionName = "conv.political." + to_string(politicalEventNumber) + ".a";
	HoI4Localisation::copyEventLocalisations("democratic_call_for_elections.a", optionName);
	callForElectionsOptionA.giveName(std::move(optionName));
	callForElections.giveOption(std::move(callForElectionsOptionA));
	EventOption callForElectionsOptionB;
	optionName = "conv.political." + to_string(politicalEventNumber) + ".b";
	HoI4Localisation::copyEventLocalisations("democratic_call_for_elections.b", optionName);
	callForElectionsOptionB.giveName(std::move(optionName));
	callForElectionsOptionB.giveScriptBlock("add_political_power = -20");
	callForElectionsOptionB.giveScriptBlock("add_ideas = democratic_opposition_voicing_protests");
	callForElections.giveOption(std::move(callForElectionsOptionB));
	politicalEvents.push_back(callForElections);
	politicalEventNumber++;
}


void HoI4::Events::addFiftyPercentEvents(const std::set<std::string>& majorIdeologies)
{
	for (auto ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		Event fiftyPercentEvent;
		fiftyPercentEvent.giveType("country_event");
		fiftyPercentEvent.giveId("conv.political." + std::to_string(politicalEventNumber));
		fiftyPercentEvent.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		HoI4Localisation::copyEventLocalisations(ideology + "_fifty_percent.t", fiftyPercentEvent.getTitle());
		std::string description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		fiftyPercentEvent.giveDescription("= " + description);
		HoI4Localisation::copyEventLocalisations(ideology + "_fifty_percent.d", description);
		fiftyPercentEvent.givePicture(getIdeologicalPicture(ideology));
		fiftyPercentEvent.setTriggeredOnly();
		EventOption optionC;
		std::string optionName = "conv.political." + std::to_string(politicalEventNumber) + ".c";
		optionC.giveName(std::move(optionName));
		HoI4Localisation::copyEventLocalisations(ideology + "_fifty_percent.c", optionName);
		if (ideology == "democratic")
		{
			for (auto ideology2: majorIdeologies)
			{
				if ((ideology2 == "neutrality") || (ideology2 == ideology))
				{
					continue;
				}
				std::string timedIdeaScript = "if = {\n";
				timedIdeaScript += "			limit = { has_government = " + ideology2 + " }\n";
				timedIdeaScript += "			add_timed_idea = { idea = " + ideology2 + "_defeated days = 730 }\n";
				timedIdeaScript += "		}";
				optionC.giveScriptBlock(std::move(timedIdeaScript));
			}
		}
		std::string setPoliticsScript = "set_politics = {\n";
		setPoliticsScript += "			ruling_party = " + ideology + "\n";
		setPoliticsScript += "			elections_allowed = ";
		(ideology == "democratic") ? setPoliticsScript += "yes\n" : setPoliticsScript += "no\n";
		setPoliticsScript += "		}";
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


void HoI4::Events::addRevolutionEvents(const std::set<std::string>& majorIdeologies)
{
	for (auto ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		Event revolutionEvent;
		revolutionEvent.giveType("country_event");
		revolutionEvent.giveId("conv.political." + std::to_string(politicalEventNumber));
		revolutionEvent.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		HoI4Localisation::copyEventLocalisations(ideology + "_revolution_event.t", revolutionEvent.getTitle());
		std::string description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		revolutionEvent.giveDescription("= " + description);
		HoI4Localisation::copyEventLocalisations(ideology + "_revolution_event.d", description);
		revolutionEvent.givePicture(getIdeologicalPicture(ideology));
		std::string trigger = "= {\n";
		trigger += "		" + ideology + " > 0.7\n";
		trigger += "		NOT = { has_government = " + ideology + " }\n";
		trigger += "		has_civil_war = no\n";
		trigger += "	}";
		revolutionEvent.giveTrigger(std::move(trigger));

		std::string mtth = "= {\n";
		mtth += "		days = 2\n";
		mtth += "	}";
		revolutionEvent.giveMeanTimeToHappen(std::move(mtth));
		std::string immediate = "= {\n";
		immediate += "		hidden_effect = { remove_ideas = " + ideology + "_revolutionaries }\n";
		immediate += "	}";
		revolutionEvent.giveImmediate(std::move(immediate));
		EventOption optionA;
		string optionName = "conv.political." + to_string(politicalEventNumber) + ".a";
		HoI4Localisation::copyEventLocalisations(ideology + "_revolution_event.a", optionName);
		optionA.giveName(std::move(optionName));
		std::string aiChance = "= {\n";
		aiChance += "			factor = 0\n";
		aiChance += "		}";
		optionA.giveAiChance(std::move(aiChance));
		std::string startCivilWar = "start_civil_war = {\n";
		startCivilWar += "			ideology = " + ideology + "\n";
		startCivilWar += "			size = 0.5\n";
		startCivilWar += "		}";
		optionA.giveScriptBlock(std::move(startCivilWar));
		revolutionEvent.giveOption(std::move(optionA));
		EventOption optionB;
		optionName = "conv.political." + std::to_string(politicalEventNumber) + ".b";
		optionB.giveName(std::move(optionName));
		HoI4Localisation::copyEventLocalisations(ideology + "_revolution_event.b", optionName);
		for (auto ideology2: majorIdeologies)
		{
			if (ideology2 == ideology)
			{
				continue;
			}
			std::string startCivilWar2 = "if = {\n";
			startCivilWar2 += "			limit = {\n";
			startCivilWar2 += "				has_government = " + ideology2 + "\n";
			startCivilWar2 += "			}\n";
			if ((ideology == "democratic") && (ideology2 != "neutrality"))
			{
				startCivilWar2 += "			add_timed_idea = { idea = " + ideology2 + "_defeated days = 730 }\n";
			}
			startCivilWar2 += "			start_civil_war = {\n";
			startCivilWar2 += "				ruling_party = " + ideology + "\n";
			startCivilWar2 += "				ideology = " + ideology2 + "\n";
			startCivilWar2 += "				size = 0.5\n";
			startCivilWar2 += "			}\n";
			if (ideology == "democratic")
			{
				startCivilWar2 += "			hold_election = ROOT\n";
			}
			startCivilWar2 += "		}";
			optionB.giveScriptBlock(std::move(startCivilWar2));
		}
		revolutionEvent.giveOption(std::move(optionB));
		politicalEvents.push_back(revolutionEvent);
		politicalEventNumber++;
	}
}


void HoI4::Events::addSuppressedEvents(const std::set<std::string>& majorIdeologies)
{
	for (auto ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		Event suppressedEvent;
		suppressedEvent.giveType("country_event");
		suppressedEvent.giveId("conv.political." + std::to_string(politicalEventNumber));
		suppressedEvent.giveTitle("conv.political." + std::to_string(politicalEventNumber) + ".t");
		HoI4Localisation::copyEventLocalisations(ideology + "_suppressed_event.t", suppressedEvent.getTitle());
		std::string description = "conv.political." + std::to_string(politicalEventNumber) + ".d";
		suppressedEvent.giveDescription("= " + description);
		HoI4Localisation::copyEventLocalisations(ideology + "_suppressed_event.d", description);
		suppressedEvent.givePicture(getIdeologicalPicture(ideology));
		std::string trigger = "= {\n";
		trigger += "		" + ideology + " < 0.3\n";
		trigger += "		has_idea = " + ideology + "_revolutionaries\n";
		trigger += "	}";
		suppressedEvent.giveTrigger(std::move(trigger));
		std::string mtth = "= {\n";
		mtth += "		days = 2\n";
		mtth += "	}";
		suppressedEvent.giveMeanTimeToHappen(std::move(mtth));
		EventOption option;
		std::string optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		option.giveName(std::move(optionName));
		HoI4Localisation::copyEventLocalisations(ideology + "_suppressed_event.a", optionName);
		option.giveScriptBlock("remove_ideas = " + ideology + "_revolutionaries");
		suppressedEvent.giveOption(std::move(option));
		politicalEvents.push_back(suppressedEvent);
		politicalEventNumber++;
	}

	int numRelevantIdeologies = 0;
	for (auto ideology: majorIdeologies)
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
		HoI4Localisation::copyEventLocalisations("abandon_neutral.t", removeNeutral.getTitle());
		for (auto ideology: majorIdeologies)
		{
			if ((ideology == "democratic") || (ideology == "neutrality"))
			{
				continue;
			}
			std::string description = "= {\n";
			description += "		text = political." + std::to_string(politicalEventNumber) + ".d_" + ideology + "\n";
			description += "		trigger = { has_government = " + ideology + " }\n";
			description += "	}";
			removeNeutral.giveDescription(std::move(description));
			HoI4Localisation::copyEventLocalisations(
				"abandon_neutral.d_" + ideology, "conv.political." + std::to_string(politicalEventNumber) + "_" + ideology
			);
		}
		removeNeutral.givePicture("GFX_report_event_journalists_speech");
		std::string trigger = "= {\n";
		trigger += "		OR = {\n";
		for (auto ideology: majorIdeologies)
		{
			if ((ideology == "democratic") || (ideology == "neutrality"))
			{
				continue;
			}
			trigger += "			has_government = " + ideology + "\n";
		}
		trigger += "		}\n";
		trigger += "		has_idea = neutrality_idea\n";
		trigger += "	}";
		removeNeutral.giveTrigger(std::move(trigger));
		std::string mtth = "= {\n";
		mtth += "		days = 2\n";
		mtth += "	}";
		removeNeutral.giveMeanTimeToHappen(std::move(mtth));
		EventOption option;
		std::string optionName = "conv.political." + std::to_string(politicalEventNumber) + ".a";
		HoI4Localisation::copyEventLocalisations("abandon_neutral.a", optionName);
		option.giveName(std::move(optionName));
		option.giveScriptBlock("remove_ideas = neutrality_idea");
		removeNeutral.giveOption(std::move(option));
		politicalEvents.push_back(removeNeutral);
	}
}


std::string HoI4::Events::getIdeologicalPicture(const std::string& ideology) const
{
	if (ideology == "communism")
	{
		return "GFX_report_event_worker_protests";
	}
	else if (ideology == "fascism")
	{
		return "GFX_report_event_fascist_gathering";
	}
	else if (ideology == "democratic")
	{
		return "GFX_report_event_journalists_speech";
	}
	else if (ideology == "radical")
	{
		return "GFX_report_event_gathering_protests";
	}
	else if (ideology == "absolutist")
	{
		return "GFX_report_event_generic_factory";
	}
	else
	{
		return "GFX_report_event_gathering_protests";
	}
}


void HoI4::Events::createWarJustificationEvents(const std::set<std::string>& majorIdeologies)
{
	int i = 1;
	for (auto majorIdeology: majorIdeologies)
	{
		for (auto majorIdeology2: majorIdeologies)
		{
			Event warJustification;
			warJustification.giveType("country_event");
			warJustification.giveId("war_justification." + std::to_string(i));
			warJustification.giveTitle("war_justification." + std::to_string(i) + ".t");
			warJustification.giveDescription("= war_justification." + std::to_string(i) + ".d");
			warJustification.givePicture("GFX_report_event_iww_demonstration");
			warJustification.setTriggeredOnly();
			std::string trigger = "= {\n";
			trigger += "		has_government = " + majorIdeology + "\n";
			trigger += "		FROM = { has_government = " + majorIdeology2 + " }\n";
			trigger += "		NOT = { has_country_flag = war_justification_last_event_political }\n";
			trigger += "	}";
			warJustification.giveTrigger(std::move(trigger));
			EventOption option;
			option.giveName("war_justification." + std::to_string(i) + ".a");
			option.giveScriptBlock(
				"FROM = { country_event = { id = war_justification." + std::to_string(i + 200) + " } }"
			);
			option.giveScriptBlock("set_country_flag = war_justification_last_event_political");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_generic");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_neighbor");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_mobilized");
			option.giveScriptBlock("clr_country_flag = war_justification_last_event_borderthreat");
			warJustification.giveOption(std::move(option));
			warJustificationEvents.push_back(warJustification);
			HoI4Localisation::copyEventLocalisations(
				"war_justification." + majorIdeology + majorIdeology2 + ".t",
				"war_justification." + std::to_string(i) + ".t"
			);
			HoI4Localisation::copyEventLocalisations(
				"war_justification." + majorIdeology + majorIdeology2 + ".d",
				"war_justification." + std::to_string(i) + ".d"
			);
			HoI4Localisation::copyEventLocalisations(
				"war_justification." + majorIdeology + majorIdeology2 + ".a",
				"war_justification." + std::to_string(i) + ".a"
			);

			Event warJustification2;
			warJustification2.giveType("country_event");
			warJustification2.giveId("war_justification." + std::to_string(200 + i));
			warJustification2.giveTitle("war_justification." + std::to_string(200 + i) + ".t");
			warJustification2.giveDescription("= war_justification." + std::to_string(200 + i) + ".d");
			warJustification2.givePicture("GFX_report_event_iww_demonstration");
			warJustification2.setTriggeredOnly();
			EventOption option2;
			option2.giveName("war_justification." + std::to_string(200 + i) + ".a");
			warJustification2.giveOption(std::move(option2));
			warJustificationEvents.push_back(warJustification2);
			HoI4Localisation::copyEventLocalisations(
				"war_justification." + majorIdeology + majorIdeology2 + "200.t",
				"war_justification." + std::to_string(200 + i) + ".t"
			);
			HoI4Localisation::copyEventLocalisations(
				"war_justification." + majorIdeology + majorIdeology2 + "200.d",
				"war_justification." + std::to_string(200 + i) + ".d"
			);
			HoI4Localisation::copyEventLocalisations(
				"war_justification." + majorIdeology + majorIdeology2 + "200.a",
				"war_justification." + std::to_string(200 + i) + ".a"
			);

			i++;
		}
	}

	Event wargoalExpired;
	wargoalExpired.giveType("country_event");
	wargoalExpired.giveId("war_justification.301");
	wargoalExpired.giveTitle("war_justification.301.t");
	wargoalExpired.giveDescription("= war_justification.301.d");
	wargoalExpired.givePicture("GFX_report_event_iww_demonstration");
	wargoalExpired.setTriggeredOnly();
	std::string trigger = "= {\n";
	trigger += "		has_war = no\n";
	trigger += "	}";
	wargoalExpired.giveTrigger(std::move(trigger));

	char letter = 'a';
	for (auto ideology: majorIdeologies)
	{
		EventOption option;
		option.giveName("war_justification.301." + std::string(1, letter));
		option.giveScriptBlock("trigger = { has_government = " + ideology + " }");
		option.giveScriptBlock("add_political_power = -30");
		option.giveScriptBlock("add_war_support = -0.03");
		if (ideology != "neutrality")
		{
			std::string addPopularity = "add_popularity = {\n";
			addPopularity += "			ideology = " + ideology + "\n";
			addPopularity += "			popularity = -0.05\n";
			addPopularity += "		}";
			option.giveScriptBlock(std::move(addPopularity));
		}
		wargoalExpired.giveOption(std::move(option));
		letter++;
	}
	warJustificationEvents.push_back(wargoalExpired);
}


void HoI4::Events::importElectionEvents(const std::set<std::string>& majorIdeologies, HoI4::OnActions& onActions)
{
	clearRegisteredKeywords();
	registerKeyword(
		std::regex("country_event"),
		[this, majorIdeologies](const std::string& type, std::istream& theStream){
			Event electionEvent(type, theStream);
			if ((majorIdeologies.count("democratic") > 0) || (electionEvent.getId() != "election.3"))
			{
				electionEvents.push_back(electionEvent);
			}
		}
	);
	registerKeyword(std::regex("[A-Za-z0-9\\_]+"), commonItems::ignoreItem);

	parseFile("blankmod/output/events/ElectionEvents.txt");

	if (majorIdeologies.count("democratic") > 0)
	{
		onActions.addElectionEvent("election.3");
	}
}


constexpr int tagAndDashSize = 4;
void HoI4::Events::addPartyChoiceEvent(
	const std::string& countryTag,
	const std::set<Vic2::Party>& parties,
	HoI4::OnActions& onActions,
	const set<string>& majorIdeologies
)
{
	Event partyChoiceEvent;

	partyChoiceEvent.giveType("country_event");
	partyChoiceEvent.giveId("election." + std::to_string(electionEventNumber));
	partyChoiceEvent.giveTitle("election." + std::to_string(electionEventNumber) + ".t");
	HoI4Localisation::copyEventLocalisations("party_choice.t", partyChoiceEvent.getTitle());
	std::string description = "election." + std::to_string(electionEventNumber) + ".d";
	partyChoiceEvent.giveDescription("= " + description);
	HoI4Localisation::copyEventLocalisations("party_choice.d", description);
	partyChoiceEvent.givePicture("GFX_report_event_usa_election_generic");
	partyChoiceEvent.setTriggeredOnly();
	std::string trigger = "= {\n";
	trigger += "		tag = " + countryTag + "\n";
	if (majorIdeologies.count("democratic") > 0)
	{
		trigger += "		OR = {\n";
		trigger += "			democratic > 0.5\n";
		trigger += "			neutrality > 0.5\n";
		trigger += "		}\n";
	}
	else
	{
		trigger += "		neutrality > 0.5\n";
	}
	trigger += "	}";
	partyChoiceEvent.giveTrigger(std::move(trigger));

	char optionLetter = 'a';
	for (auto party: parties)
	{
		if ((party.getIdeology() == "conservative"))
		{
			std::string partyName = party.getName();
			std::string trimmedName = partyName.substr(tagAndDashSize, partyName.size());

			std::string optionName = "election." + std::to_string(electionEventNumber) + optionLetter;
			EventOption option;
			option.giveName(std::move(optionName));
			if (majorIdeologies.count("democratic") > 0)
			{
				option.giveScriptBlock(
					"set_party_name = { " \
						"ideology = democratic " \
						"long_name = " + countryTag + "_" + trimmedName + "_party " +
						"name = " + countryTag + "_" + trimmedName + "_party" \
					"}"
				);
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = conservatism");
			}
			else
			{
				option.giveScriptBlock(
					"set_party_name = { " \
						"ideology = neutrality " \
						"long_name = " + countryTag + "_" + trimmedName + "_party " +
						"name = " + countryTag + "_" + trimmedName + "_party " \
					"}"
				);
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = conservatism_neutral");
			}
			partyChoiceEvent.giveOption(std::move(option));
			HoI4Localisation::addEventLocalisationFromVic2(partyName, optionName);
			optionLetter++;
		}
		if ((party.getIdeology() == "liberal"))
		{
			std::string partyName = party.getName();
			std::string trimmedName = partyName.substr(tagAndDashSize, partyName.size());

			std::string optionName = "election." + std::to_string(electionEventNumber) + optionLetter;
			EventOption option;
			option.giveName(std::move(optionName));
			if (majorIdeologies.count("democratic") > 0)
			{
				option.giveScriptBlock(
					"set_party_name = { " \
						"ideology = democratic " \
						"long_name = " + countryTag + "_" + trimmedName + "_party " +
						"name = " + countryTag + "_" + trimmedName + "_party " \
					"}"
				);
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = liberalism");
			}
			else
			{
				option.giveScriptBlock(
					"set_party_name = { " \
						"ideology = neutrality " \
						"long_name = " + countryTag + "_" + trimmedName + "_party " +
						"name = " + countryTag + "_" + trimmedName + "_party " \
					"}"
				);
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = liberalism_neutral");
			}
			partyChoiceEvent.giveOption(std::move(option));
			HoI4Localisation::addEventLocalisationFromVic2(partyName, optionName);
			optionLetter++;
		}
		if ((party.getIdeology() == "socialist"))
		{
			std::string partyName = party.getName();
			std::string trimmedName = partyName.substr(tagAndDashSize, partyName.size());

			std::string optionName = "election." + std::to_string(electionEventNumber) + optionLetter;
			EventOption option;
			option.giveName(std::move(optionName));
			if (majorIdeologies.count("democratic") > 0)
			{
				option.giveScriptBlock(
					"set_party_name = { " \
						"ideology = democratic " \
						"long_name = " + countryTag + "_" + trimmedName + "_party " +
						"name = " + countryTag + "_" + trimmedName + "_party " \
					"}"
				);
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = socialism");
			}
			else
			{
				option.giveScriptBlock(
					"set_party_name = { " \
						"ideology = neutrality " \
						"long_name = " + countryTag + "_" + trimmedName + "_party " +
						"name = " + countryTag + "_" + trimmedName + "_party " \
					"}"
				);
				option.giveScriptBlock("retire_country_leader = yes");
				option.giveScriptBlock("set_country_leader_ideology = socialism_neutral");
			}
			partyChoiceEvent.giveOption(std::move(option));
			HoI4Localisation::addEventLocalisationFromVic2(partyName, optionName);
			optionLetter++;
		}
	}

	onActions.addElectionEvent(partyChoiceEvent.getId());
	electionEvents.push_back(partyChoiceEvent);
	electionEventNumber++;
}


void HoI4::Events::createStabilityEvents(const std::set<std::string>& majorIdeologies)
{
	clearRegisteredKeywords();
	registerKeyword(std::regex("add_namespace"), commonItems::ignoreString);
	registerKeyword(std::regex("country_event"), [this](const std::string& type, std::istream& theStream)
		{
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
		}
	);

	parseFile(theConfiguration.getHoI4Path() + "/events/stability_events.txt");

	if (majorIdeologies.count("democratic") == 0)
	{
		auto lowStabilitySelector = stabilityEvents.find("stability.3");
		std::string mtth = "= {\n";
		mtth += "		days = 360\n";
		mtth += "		modifier = {\n";
		mtth += "			factor = 0.75\n";
		mtth += "			OR = {\n";
		mtth += "				has_stability < 0.4\n";
		mtth += "				has_war_support < 0.4\n";
		mtth += "			}\n";
		mtth += "		}\n";
		mtth += "		modifier = {\n";
		mtth += "			factor = 0.75\n";
		mtth += "			OR = {\n";
		mtth += "				has_stability < 0.2\n";
		mtth += "				has_war_support < 0.2\n";
		mtth += "			}\n";
		mtth += "		}\n";
		mtth += "	}";
		lowStabilitySelector->second.giveMeanTimeToHappen(std::move(mtth));
	}

	auto conscriptionRebellion = stabilityEvents.find("stability.33");
	conscriptionRebellion->second.clearOptions();
	EventOption option;
	option.giveName("stability.33.a");
	std::string startExtermistCivilWar = "if = {\n";
	if (majorIdeologies.count("democratic") > 0)
	{
		startExtermistCivilWar += "			limit = { has_government = democratic }\n";
	}
	else
	{
		startExtermistCivilWar += "			limit = { has_government = neutrality }\n";
	}
	if (majorIdeologies.count("communism") > 0)
	{
		startExtermistCivilWar += "			start_civil_war = { ideology = communism size = 0.35 }\n";
	}
	else if (majorIdeologies.count("radical") > 0)
	{
		startExtermistCivilWar += "			start_civil_war = { ideology = radical size = 0.35 }\n";
	}
	else if (majorIdeologies.count("fascism") > 0)
	{
		startExtermistCivilWar += "			start_civil_war = { ideology = fascism size = 0.35 }\n";
	}
	else if (majorIdeologies.count("absolutist") > 0)
	{
		startExtermistCivilWar += "			start_civil_war = { ideology = absolutist size = 0.35 }\n";
	}
	startExtermistCivilWar += "		}";
	option.giveScriptBlock(std::move(startExtermistCivilWar));
	if (majorIdeologies.count("democratic") > 0)
	{
		std::string startDemocraticCivilWar = "if = {\n";
		startDemocraticCivilWar += "			limit = { \n";
		startDemocraticCivilWar += "				OR = {\n";
		for (auto majorIdeology: majorIdeologies)
		{
			if ((majorIdeology == "democratic") || (majorIdeology == "neutrality"))
			{
				continue;
			}

			startDemocraticCivilWar += "					has_government = " + majorIdeology + "\n";
		}
		startDemocraticCivilWar += "				} \n";
		startDemocraticCivilWar += "			}\n";
		startDemocraticCivilWar += "			start_civil_war = { ideology = democratic size = 0.45 }\n";
		startDemocraticCivilWar += "		}\n";
		option.giveScriptBlock(std::move(startDemocraticCivilWar));
	}
	option.giveScriptBlock("clr_country_flag = crisis_in_progress");
	option.giveScriptBlock("clr_country_flag = crisis_solution_in_progress");
	option.giveScriptBlock("set_country_flag = { flag = draft_dodging_resolved days = 90 }");
	conscriptionRebellion->second.giveOption(std::move(option));
}


std::optional<int> HoI4::Events::getEventNumber(const std::string& eventName) const
{
	auto eventRecord = eventNumbers.find(eventName);
	if (eventRecord != eventNumbers.end())
	{
		return eventRecord->second;
	}
	else
	{
		return std::nullopt;
	}
}
