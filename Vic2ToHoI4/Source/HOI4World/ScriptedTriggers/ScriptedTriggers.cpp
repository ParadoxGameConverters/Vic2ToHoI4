#include "ScriptedTriggers.h"
#include "ParserHelpers.h"



void HoI4::ScriptedTriggers::importScriptedTriggers(const Configuration& theConfiguration)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& name, std::istream& theStream)
	{
		ScriptedTrigger scriptedTrigger(name);
		const commonItems::stringOfObject bodyString(theStream);
		scriptedTrigger.setBody(bodyString.getString());
		ideologyScriptedTriggers.push_back(scriptedTrigger);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/scripted_triggers/ideology_scripted_triggers.txt");
	clearRegisteredKeywords();

	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& name, std::istream& theStream)
	{
		ScriptedTrigger scriptedTrigger(name);
		const commonItems::stringOfObject bodyString(theStream);
		scriptedTrigger.setBody(bodyString.getString());
		electionsScriptedTriggers.push_back(scriptedTrigger);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/scripted_triggers/Elections_scripted_triggers.txt");
	clearRegisteredKeywords();

	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& name, std::istream& theStream)
	{
		ScriptedTrigger scriptedTrigger(name);
		const commonItems::stringOfObject bodyString(theStream);
		scriptedTrigger.setBody(bodyString.getString());
		lawsWarSupportTriggers.push_back(scriptedTrigger);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/scripted_triggers/laws_war_support.txt");
	clearRegisteredKeywords();
}


void HoI4::ScriptedTriggers::replaceIdeologyScriptedTrigger(
	const std::string_view name,
	const std::string& replacementBody
)
{
	for (auto& scriptedTrigger: ideologyScriptedTriggers)
	{
		if (scriptedTrigger.getName() == name)
		{
			scriptedTrigger.setBody(replacementBody);
			break;
		}
	}
}


void HoI4::ScriptedTriggers::replaceElectionsScriptedTrigger(
	const std::string_view name,
	const std::string& replacementBody
)
{
	for (auto& scriptedTrigger: electionsScriptedTriggers)
	{
		if (scriptedTrigger.getName() == name)
		{
			scriptedTrigger.setBody(replacementBody);
			break;
		}
	}
}


void HoI4::ScriptedTriggers::replaceLawsWarSupportTriggers(const std::map<std::string_view, std::string>& replacements)
{
	for (auto& scriptedTrigger: lawsWarSupportTriggers)
	{
		if (auto replacement = replacements.find(scriptedTrigger.getName()); replacement != replacements.end())
		{
			scriptedTrigger.setBody(replacement->second);
		}
	}
}


void HoI4::ScriptedTriggers::updateScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	updateIdeologyScriptedTriggers(majorIdeologies);
	updateElectionsScriptedTriggers(majorIdeologies);
	updateLawsWarSupportTriggers(majorIdeologies);
}


void HoI4::ScriptedTriggers::updateIdeologyScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	std::string body = "= {\n";
	body += "\tOR = {\n";
	for (const auto& ideology : majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		body += "\t\tAND = {\n";
		body += "\t\t\thas_government = " + ideology + "\n";
		body += "\t\t\tROOT = {\n";
		body += "\t\t\t\tOR = {\n";
		for (const auto& secondIdeology : majorIdeologies)
		{
			if ((secondIdeology == ideology) || (secondIdeology == "neutrality"))
			{
				continue;
			}
			body += "\t\t\t\t\thas_government = " + secondIdeology + "\n";
		}
		body += "\t\t\t\t}\n";
		body += "\t\t\t}\n";
		body += "\t\t}\n";
	}
	body += "\t}\n";
	body += "}";

	replaceIdeologyScriptedTrigger("is_enemy_ideology", body);
}



void HoI4::ScriptedTriggers::updateElectionsScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	std::string supportBody = "= {\n";
	for (const auto& ideology : majorIdeologies)
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

	replaceElectionsScriptedTrigger("can_lose_democracy_support", supportBody);
}


std::string getHasUnsupportedManpowerLawBody(const std::set<std::string>& majorIdeologies);
std::string getHasExcessiveArmySizeBody(const std::set<std::string>& majorIdeologies);
void HoI4::ScriptedTriggers::updateLawsWarSupportTriggers(const std::set<std::string>& majorIdeologies)
{
	std::map<std::string_view, std::string> replacements;
	replacements.insert(
		std::make_pair(
			"has_unsupported_manpower_law",
			getHasUnsupportedManpowerLawBody(majorIdeologies)
		)
	);
	replacements.insert(std::make_pair("has_excessive_army_size", getHasExcessiveArmySizeBody(majorIdeologies)));
	replaceLawsWarSupportTriggers(replacements);
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
	for (const auto& majorIdeology : majorIdeologies)
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
	for (const auto& majorIdeology : majorIdeologies)
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
	if (majorIdeologies.count("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.count("radical"))
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
	if (majorIdeologies.count("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.count("radical"))
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
	if (majorIdeologies.count("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.count("radical"))
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
	if (majorIdeologies.count("communism"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = communism\n";
		body += "\t\t\t}\n";
	}
	if (majorIdeologies.count("radical"))
	{
		body += "\t\t\tNOT = {\n";
		body += "\t\t\t\thas_government = radical\n";
		body += "\t\t\t}\n";
	}
	body += "\t\t}\n";
	if (majorIdeologies.count("democratic"))
	{
		body += "\t\tAND = {\n";
		body += "\t\t\thas_army_manpower = { size = 2500000 }\n";
		body += "\t\t\thas_manpower < 1\n";
		body += "\t\t\thas_government = democratic\n";
		body += "\t\t}\n";
	}
	if (majorIdeologies.count("fascism"))
	{
		body += "\t\tAND = {\n";
		body += "\t\t\thas_army_manpower = { size = 3000000 }\n";
		body += "\t\t\thas_manpower < 1\n";
		body += "\t\t\thas_government = fascism\n";
		body += "\t\t}\n";
		body += "\t}\n";
	}
	if (majorIdeologies.count("absolutist"))
	{
		body += "\t\tAND = {\n";
		body += "\t\t\thas_army_manpower = { size = 3000000 }\n";
		body += "\t\t\thas_manpower < 1\n";
		body += "\t\t\thas_government = absolutist\n";
		body += "\t\t}\n";
		body += "\t}\n";
	}
	body += "}\n";
	return body;
}