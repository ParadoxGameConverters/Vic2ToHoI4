#include "src/HOI4World/ScriptedTriggers/ScriptedTriggersUpdater.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/ScriptedTriggers/ScriptedTrigger.h"



void updateIdeologyScriptedTriggers(HoI4::ScriptedTriggers& scriptedTriggers,
	 const std::set<std::string>& majorIdeologies);
void updateElectionsScriptedTriggers(HoI4::ScriptedTriggers& scriptedTriggers,
	 const std::set<std::string>& majorIdeologies);
void updateLawsWarSupportTriggers(HoI4::ScriptedTriggers& scriptedTriggers,
	 const std::set<std::string>& majorIdeologies);
void HoI4::updateScriptedTriggers(ScriptedTriggers& scriptedTriggers, const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating scripted triggers";
	updateIdeologyScriptedTriggers(scriptedTriggers, majorIdeologies);
	updateElectionsScriptedTriggers(scriptedTriggers, majorIdeologies);
	updateLawsWarSupportTriggers(scriptedTriggers, majorIdeologies);
}


void updateIdeologyScriptedTriggers(HoI4::ScriptedTriggers& scriptedTriggers,
	 const std::set<std::string>& majorIdeologies)
{
	std::string is_enemy_ideology_body = "= {\n";
	is_enemy_ideology_body += "\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		is_enemy_ideology_body += "\t\tAND = {\n";
		is_enemy_ideology_body += "\t\t\thas_government = " + ideology + "\n";
		is_enemy_ideology_body += "\t\t\tROOT = {\n";
		is_enemy_ideology_body += "\t\t\t\tOR = {\n";
		for (const auto& secondIdeology: majorIdeologies)
		{
			if ((secondIdeology == ideology) || (secondIdeology == "neutrality"))
			{
				continue;
			}
			is_enemy_ideology_body += "\t\t\t\t\thas_government = " + secondIdeology + "\n";
		}
		is_enemy_ideology_body += "\t\t\t\t}\n";
		is_enemy_ideology_body += "\t\t\t}\n";
		is_enemy_ideology_body += "\t\t}\n";
	}
	is_enemy_ideology_body += "\t}\n";
	is_enemy_ideology_body += "}";
	scriptedTriggers.replaceIdeologyScriptedTrigger("is_enemy_ideology", is_enemy_ideology_body);

	std::string has_same_ideology_body = "= {\n";
	has_same_ideology_body += "\tcustom_trigger_tooltip = {\n";
	has_same_ideology_body += "\t\ttooltip = has_same_ideology_tt\n";
	has_same_ideology_body += "\t\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		has_same_ideology_body += "\t\t\tAND = {\n";
		has_same_ideology_body += "\t\t\t\thas_government = " + ideology + "\n";
		has_same_ideology_body += "\t\t\t\tROOT = { has_government = " + ideology + " }\n";
		has_same_ideology_body += "\t\t\t}\n";
	}
	has_same_ideology_body += "\t\t}\n";
	has_same_ideology_body += "\t}\n";
	has_same_ideology_body += "}\n";
	scriptedTriggers.replaceIdeologyScriptedTrigger("has_same_ideology", has_same_ideology_body);

	if (majorIdeologies.contains("communism"))
	{
		std::string big_communist_exists_body = "= {\n";
		big_communist_exists_body += "\tany_other_country = {\n";
		big_communist_exists_body += "\t\tis_major = yes \n";
		big_communist_exists_body += "\t\thas_government = communism\n";
		big_communist_exists_body += "\t\thas_capitulated = no \n";
		big_communist_exists_body += "\t\texists = yes \n";
		big_communist_exists_body += "\t}\n";
		big_communist_exists_body += "}\n";

		auto bigCommunistExists = HoI4::ScriptedTrigger("big_communist_exists");
		bigCommunistExists.setBody(big_communist_exists_body);
		scriptedTriggers.addIdeologyTrigger(bigCommunistExists);
	}

	if (majorIdeologies.contains("fascism"))
	{
		std::string big_fascist_exists_body = "= {\n";
		big_fascist_exists_body += "\tany_other_country = {\n";
		big_fascist_exists_body += "\t\tis_major = yes \n";
		big_fascist_exists_body += "\t\thas_government = fascism\n";
		big_fascist_exists_body += "\t\thas_capitulated = no \n";
		big_fascist_exists_body += "\t\texists = yes \n";
		big_fascist_exists_body += "\t}\n";
		big_fascist_exists_body += "}\n";

		auto bigFascistExists = HoI4::ScriptedTrigger("big_fascist_exists");
		bigFascistExists.setBody(big_fascist_exists_body);
		scriptedTriggers.addIdeologyTrigger(bigFascistExists);

		std::string is_fascist_seller_trigger_body = "= {\n";
		is_fascist_seller_trigger_body += "\tNOT = { has_war_with = ROOT\t}\n";
		is_fascist_seller_trigger_body += "\thas_government = fascism \n";
		is_fascist_seller_trigger_body += "}\n";

		auto isFascistSeller = HoI4::ScriptedTrigger("is_fascist_seller_trigger");
		isFascistSeller.setBody(is_fascist_seller_trigger_body);
		scriptedTriggers.addIdeologyTrigger(isFascistSeller);
	}

	if (majorIdeologies.contains("democratic"))
	{
		std::string is_democratic_seller_trigger_body = "= {\n";
		is_democratic_seller_trigger_body += "\tcustom_trigger_tooltip = {\n";
		is_democratic_seller_trigger_body += "\t\ttooltip = \"Democratic Countries\"\n";
		is_democratic_seller_trigger_body += "\t\tFROM = {\n";
		is_democratic_seller_trigger_body += "\t\t\thas_government = democratic\n";
		is_democratic_seller_trigger_body += "\t\t}\n";
		is_democratic_seller_trigger_body += "\t}\n";
		is_democratic_seller_trigger_body += "}\n";

		auto isDemocraticSeller = HoI4::ScriptedTrigger("is_democratic_seller_trigger");
		isDemocraticSeller.setBody(is_democratic_seller_trigger_body);
		scriptedTriggers.addIdeologyTrigger(isDemocraticSeller);

		std::string is_democracy_seller_trigger_body = "= {\n";
		is_democracy_seller_trigger_body += "\tNOT = { has_war_with = ROOT\t}\n";
		is_democracy_seller_trigger_body += "\thas_government = democratic \n";
		is_democracy_seller_trigger_body += "}\n";

		auto isDemocracySeller = HoI4::ScriptedTrigger("is_democracy_seller_trigger");
		isDemocracySeller.setBody(is_democracy_seller_trigger_body);
		scriptedTriggers.addIdeologyTrigger(isDemocracySeller);
	}
}



void updateElectionsScriptedTriggers(HoI4::ScriptedTriggers& scriptedTriggers,
	 const std::set<std::string>& majorIdeologies)
{
	std::string supportBody = "= {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		if (ideology == "democratic")
		{
			supportBody += "\tdemocratic > 0.65\n";
		}
		else
		{
			supportBody += "\t" + ideology + " < 0.18\n";
		}
	}
	supportBody += "}";

	scriptedTriggers.replaceElectionsScriptedTrigger("can_lose_democracy_support", supportBody);
}


std::string getHasUnsupportedManpowerLawBody(const std::set<std::string>& majorIdeologies);
std::string getHasExcessiveArmySizeBody(const std::set<std::string>& majorIdeologies);
void updateLawsWarSupportTriggers(HoI4::ScriptedTriggers& scriptedTriggers,
	 const std::set<std::string>& majorIdeologies)
{
	std::map<std::string_view, std::string> replacements;
	replacements.insert(
		 std::make_pair("has_unsupported_manpower_law", getHasUnsupportedManpowerLawBody(majorIdeologies)));
	replacements.insert(std::make_pair("has_excessive_army_size", getHasExcessiveArmySizeBody(majorIdeologies)));
	scriptedTriggers.replaceLawsWarSupportTriggers(replacements);
}


std::string getHasUnsupportedManpowerLawBody(const std::set<std::string>& majorIdeologies)
{
	std::string unsupportedManpowerBody = "= {\n";
	unsupportedManpowerBody += "\tif = {\n";
	unsupportedManpowerBody += "\t\tlimit = {\n";
	unsupportedManpowerBody += "\t\t\thas_idea = limited_conscription\n";
	unsupportedManpowerBody += "\t\t}\n";
	unsupportedManpowerBody += "\t\thas_idea = limited_conscription\n";
	unsupportedManpowerBody += "\t\thas_war_support < 0.1\n";
	unsupportedManpowerBody += "\t}\n";
	unsupportedManpowerBody += "\telse_if = {\n";
	unsupportedManpowerBody += "\t\tlimit = {\n";
	unsupportedManpowerBody += "\t\t\thas_idea = extensive_conscription\n";
	unsupportedManpowerBody += "\t\t}\n";
	unsupportedManpowerBody += "\t\thas_idea = extensive_conscription\n";
	unsupportedManpowerBody += "\t\thas_war_support < 0.2\n";
	for (const auto& majorIdeology: majorIdeologies)
	{
		if ((majorIdeology == "democratic") || (majorIdeology == "neutrality"))
		{
			continue;
		}

		unsupportedManpowerBody += "\t\tNOT = { has_government = " + majorIdeology + " }\n";
	}
	unsupportedManpowerBody += "\t}\n";
	unsupportedManpowerBody += "\telse_if = {\n";
	unsupportedManpowerBody += "\t\tlimit = {\n";
	unsupportedManpowerBody += "\t\t\thas_idea = service_by_requirement\n";
	unsupportedManpowerBody += "\t\t}\n";
	unsupportedManpowerBody += "\t\thas_idea = service_by_requirement\n";
	unsupportedManpowerBody += "\t\thas_war_support < 0.6\n";
	for (const auto& majorIdeology: majorIdeologies)
	{
		if ((majorIdeology == "democratic") || (majorIdeology == "neutrality"))
		{
			continue;
		}

		unsupportedManpowerBody += "\t\tNOT = { has_government = " + majorIdeology + " }\n";
	}
	unsupportedManpowerBody += "\t}\n";
	unsupportedManpowerBody += "\telse_if = {\n";
	unsupportedManpowerBody += "\t\tlimit = {\n";
	unsupportedManpowerBody += "\t\t\thas_idea = all_adults_serve\n";
	unsupportedManpowerBody += "\t\t}\n";
	unsupportedManpowerBody += "\t\thas_idea = all_adults_serve\n";
	unsupportedManpowerBody += "\t}\n";
	unsupportedManpowerBody += "\telse_if = {\n";
	unsupportedManpowerBody += "\t\tlimit = {\n";
	unsupportedManpowerBody += "\t\t\thas_idea = scraping_the_barrel\n";
	unsupportedManpowerBody += "\t\t}\n";
	unsupportedManpowerBody += "\t\thas_idea = scraping_the_barrel\n";
	unsupportedManpowerBody += "\t}\n";
	unsupportedManpowerBody += "\telse = {\n";
	unsupportedManpowerBody += "\t\talways = no\n";
	unsupportedManpowerBody += "\t}\n";
	unsupportedManpowerBody += "}\n";
	return unsupportedManpowerBody;
}


std::string getHasExcessiveArmySizeBody(const std::set<std::string>& majorIdeologies)
{
	std::string body = "= {\n";
	body += "\tOR = {\n";
	body += "\t\tAND = {\n";
	body += "\t\t\tnum_of_factories < 25\n";
	body += "\t\t\thas_army_manpower = { size = 250000 }\n";
	body += "\t\t\thas_manpower < 1\n";
	if (majorIdeologies.contains("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.contains("radical"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = radical\n";
		body += "\t\t\t}\n";
	}
	body += "\t\t}\n";
	body += "\t\tAND = {\n";
	body += "\t\tnum_of_factories < 50\n";
	body += "\t\thas_army_manpower = { size = 500000 }\n";
	body += "\t\thas_manpower < 1\n";
	if (majorIdeologies.contains("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.contains("radical"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = radical\n";
		body += "\t\t\t}\n";
	}
	body += "\t\t}\n";
	body += "\t\tAND = {\n";
	body += "\t\t\tnum_of_factories < 75\n";
	body += "\t\t\thas_army_manpower = { size = 750000 }\n";
	body += "\t\t\thas_manpower < 1\n";
	if (majorIdeologies.contains("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.contains("radical"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = radical\n";
		body += "\t\t\t}\n";
	}
	body += "\t\t}\n";
	body += "\t\tAND = {\n";
	body += "\t\t\tnum_of_factories < 100\n";
	body += "\t\t\thas_army_manpower = { size = 1000000 }\n";
	body += "\t\t\thas_manpower < 1\n";
	if (majorIdeologies.contains("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.contains("radical"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = radical\n";
		body += "\t\t\t}\n";
	}
	body += "\t\t}\n";
	if (majorIdeologies.contains("democratic"))
	{
		body += "\t\tAND = {\n";
		body += "\t\t\thas_army_manpower = { size = 2500000 }\n";
		body += "\t\t\thas_manpower < 1\n";
		body += "\t\t\thas_government = democratic\n";
		body += "\t\t}\n";
	}
	if (majorIdeologies.contains("fascism"))
	{
		body += "\t\tAND = {\n";
		body += "\t\t\thas_army_manpower = { size = 3000000 }\n";
		body += "\t\t\thas_manpower < 1\n";
		body += "\t\t\thas_government = fascism\n";
		body += "\t\t}\n";
	}
	if (majorIdeologies.contains("absolutist"))
	{
		body += "\t\tAND = {\n";
		body += "\t\t\thas_army_manpower = { size = 3000000 }\n";
		body += "\t\t\thas_manpower < 1\n";
		body += "\t\t\thas_government = absolutist\n";
		body += "\t\t}\n";
	}
	body += "\t}\n";
	body += "}\n";
	return body;
}