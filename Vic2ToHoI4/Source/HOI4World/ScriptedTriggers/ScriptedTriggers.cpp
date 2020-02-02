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
}



void HoI4::ScriptedTriggers::updateScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	updateIdeologyScriptedTriggers(majorIdeologies);
	updateElectionsScriptedTriggers(majorIdeologies);
}


void HoI4::ScriptedTriggers::updateIdeologyScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	for (auto& scriptedTrigger: ideologyScriptedTriggers)
	{
		if (scriptedTrigger.getName() == "is_enemy_ideology")
		{
			std::string body = "\tOR = {\n";
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
			body += "\t}";
			scriptedTrigger.setBody(body);
		}
	}
}



void HoI4::ScriptedTriggers::updateElectionsScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	std::string unityBody = "\thas_stability > 60\n";
	unityBody += "\tOR = {\n";
	unityBody += "\t\thas_war = no\n";
	unityBody += "\t\tAND = {\n";
	unityBody += "\t\t\thas_war = yes\n";
	unityBody += "\t\t\tsurrender_progress < 0.1\n";
	unityBody += "\t\t}\n";
	unityBody += "\t}";
	ScriptedTrigger canLoseUnity("can_lose_unity");
	canLoseUnity.setBody(unityBody);
	electionsScriptedTriggers.push_back(canLoseUnity);

	std::string supportBody;
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
	ScriptedTrigger canLoseDemocracySupport("can_lose_democracy_support");
	canLoseDemocracySupport.setBody(supportBody);
	electionsScriptedTriggers.push_back(canLoseDemocracySupport);
}