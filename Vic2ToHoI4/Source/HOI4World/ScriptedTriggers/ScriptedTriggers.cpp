#include "ScriptedTriggers.h"



void HoI4::ScriptedTriggers::createScriptedTriggers(const std::set<std::string>& majorIdeologies)
{
	std::string body = "\tOR = {\n";
	for (const auto& ideology : majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		body += "\t\tAND = { \n";
		body += "\t\t\thas_government = " + ideology + "\n";
		body += "\t\t\tROOT = { \n";
		body += "\t\t\t\tOR = { \n";
		for (const auto& secondIdeology: majorIdeologies)
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

	ScriptedTrigger isEnemyIdeology("is_enemy_ideology");
	isEnemyIdeology.setBody(body);

	ideologyScriptedTriggers.push_back(isEnemyIdeology);
}