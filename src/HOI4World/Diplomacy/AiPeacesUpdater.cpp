#include "AiPeacesUpdater.h"
#include "external/common_items/Log.h"



void HoI4::updateAiPeaces(AiPeaces& aiPeaces, const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating AI peaces";

	std::string newFacismEnable = "= {\n";
	newFacismEnable += "\t\tOR = {\n";
	newFacismEnable += "\t\t\thas_government = fascism\n";
	newFacismEnable += "\t\t\tAND = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if ((ideology == "fascism") || (ideology == "neutrality"))
		{
			continue;
		}
		newFacismEnable += "\t\t\t\tNOT = { has_government = " + ideology + " }\n";
	}
	newFacismEnable += "\t\t\t\tOR = {\n";
	newFacismEnable += "\t\t\t\t\tany_country = {\n";
	newFacismEnable += "\t\t\t\t\t\tis_in_faction_with = ROOT\n";
	newFacismEnable += "\t\t\t\t\t\tis_faction_leader = yes\n";
	newFacismEnable += "\t\t\t\t\t\thas_government = fascism\n";
	newFacismEnable += "\t\t\t\t\t}\n";
	newFacismEnable += "\t\t\t\t\tis_in_faction = no\n";
	newFacismEnable += "\t\t\t\t\tis_faction_leader = yes\n";
	newFacismEnable += "\t\t\t\t}\n";
	newFacismEnable += "\t\t\t}\n";
	newFacismEnable += "\t\t}\n";
	newFacismEnable += "\t}";

	aiPeaces.updateAiPeace("fascist_peace", newFacismEnable);

	std::string newAbsolutistEnable = "= {\n";
	newAbsolutistEnable += "\t\tOR = {\n";
	newAbsolutistEnable += "\t\t\thas_government = absolutist\n";
	newAbsolutistEnable += "\t\t\tAND = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if ((ideology == "absolutist") || (ideology == "neutrality"))
		{
			continue;
		}
		newAbsolutistEnable += "\t\t\t\tNOT = { has_government = " + ideology + " }\n";
	}
	newAbsolutistEnable += "\t\t\t\tOR = {\n";
	newAbsolutistEnable += "\t\t\t\t\tany_country = {\n";
	newAbsolutistEnable += "\t\t\t\t\t\tis_in_faction_with = ROOT\n";
	newAbsolutistEnable += "\t\t\t\t\t\tis_faction_leader = yes\n";
	newAbsolutistEnable += "\t\t\t\t\t\thas_government = absolutist\n";
	newAbsolutistEnable += "\t\t\t\t\t}\n";
	newAbsolutistEnable += "\t\t\t\t\tis_in_faction = no\n";
	newAbsolutistEnable += "\t\t\t\t\tis_faction_leader = yes\n";
	newAbsolutistEnable += "\t\t\t\t}\n";
	newAbsolutistEnable += "\t\t\t}\n";
	newAbsolutistEnable += "\t\t}\n";
	newAbsolutistEnable += "\t}";

	aiPeaces.updateAiPeace("absolutist_peace", newAbsolutistEnable);
}