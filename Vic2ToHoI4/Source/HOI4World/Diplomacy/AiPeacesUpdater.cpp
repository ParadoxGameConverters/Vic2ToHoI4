#include "AiPeacesUpdater.h"
#include "Log.h"



void HoI4::updateAiPeaces(AiPeaces& aiPeaces, const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating AI peaces";

	std::string newEnable = "= {\n";
	newEnable += "\t\tOR = {\n";
	newEnable += "\t\t\thas_government = fascism\n";
	newEnable += "\t\t\tAND = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if ((ideology == "fascism") || (ideology == "neutrality"))
		{
			continue;
		}
		newEnable += "\t\t\t\tNOT = { has_government = " + ideology + " }\n";
	}
	newEnable += "\t\t\t\tOR = {\n";
	newEnable += "\t\t\t\t\tany_country = {\n";
	newEnable += "\t\t\t\t\t\tis_in_faction_with = ROOT\n";
	newEnable += "\t\t\t\t\t\tis_faction_leader = yes\n";
	newEnable += "\t\t\t\t\t\thas_government = fascism\n";
	newEnable += "\t\t\t\t\t}\n";
	newEnable += "\t\t\t\t\tis_in_faction = no\n";
	newEnable += "\t\t\t\t\tis_faction_leader = yes\n";
	newEnable += "\t\t\t\t}\n";
	newEnable += "\t\t\t}\n";
	newEnable += "\t\t}\n";
	newEnable += "\t}";

	aiPeaces.updateAiPeace("fascist_peace", newEnable);
}