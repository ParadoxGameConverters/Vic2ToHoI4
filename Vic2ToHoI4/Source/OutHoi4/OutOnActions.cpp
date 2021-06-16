#include "OutOnActions.h"
#include <fstream>



constexpr int firstWarJustificationEvent = 17;
constexpr int numNonIdeologicalEvents = 4;



void HoI4::outputOnActions(const OnActions& onActions,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName)
{
	std::ofstream onActionsFile("output/" + outputName + "/common/on_actions/99_converter_on_actions.txt");
	if (!onActionsFile.is_open())
	{
		throw std::runtime_error("Could not create NF_events.txt");
	}

	onActionsFile << "on_actions = {\n";
	onActionsFile << "\t# country\n";
	onActionsFile << "\ton_new_term_election = {\n";
	onActionsFile << "\t\trandom_events = {\n";
	for (const auto& event: onActions.getElectionEvents())
	{
		onActionsFile << "\t\t\t100 = " << event << "\n";
	}
	onActionsFile << "\t\t}\n";
	onActionsFile << "\t}\n";
	onActionsFile << "\ton_government_change = {\n";
	onActionsFile << "\t\teffect = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if ((ideology == "democratic") || (ideology == "neutrality"))
		{
			continue;
		}

		onActionsFile << "\t\t\tif = {\n";
		onActionsFile << "\t\t\t\tlimit = { has_government = " + ideology + " }\n";
		onActionsFile << "\t\t\t\tif = {\n";
		onActionsFile << "\t\t\t\t\tlimit = { has_idea = " + ideology + "_partisans_recruiting }\n";
		onActionsFile << "\t\t\t\t\tremove_ideas = " + ideology + "_partisans_recruiting\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t\tif = {\n";
		onActionsFile << "\t\t\t\t\tlimit = { has_idea = " + ideology + "_revolutionaries }\n";
		onActionsFile << "\t\t\t\t\tremove_ideas = " + ideology + "_revolutionaries\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t\tif = {\n";
		onActionsFile << "\t\t\t\t\tlimit = { has_idea = " + ideology + "_defeated }\n";
		onActionsFile << "\t\t\t\t\tremove_ideas = " + ideology + "_defeated\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t}\n";
	}

	if (majorIdeologies.contains("democratic"))
	{
		onActionsFile << "\t\t\tif = {\n";
		onActionsFile << "\t\t\t\tlimit = { has_government = democratic }\n";
		onActionsFile << "\t\t\t\tif = {\n";
		onActionsFile << "\t\t\t\t\tlimit = { has_idea = democratic_opposition_voicing_protests }\n";
		onActionsFile << "\t\t\t\t\tremove_ideas = democratic_opposition_voicing_protests\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t\tif = {\n";
		onActionsFile << "\t\t\t\t\tlimit = { has_idea = democratic_revolutionaries }\n";
		onActionsFile << "\t\t\t\t\tremove_ideas = democratic_revolutionaries\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t\tif = {\n";
		onActionsFile << "\t\t\t\t\tlimit = { has_idea = reign_of_terror }\n";
		onActionsFile << "\t\t\t\t\tremove_ideas = reign_of_terror\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t}\n";
	}
	onActionsFile << "\t\t}\n";
	onActionsFile << "\t}\n";

	if (majorIdeologies.contains("democratic"))
	{
		onActionsFile << "\ton_coup_succeeded = {\n";
		onActionsFile << "\t\teffect = {\n";
		onActionsFile << "\t\t\t#Turn elections on for democracies created from coup\n";
		onActionsFile << "\t\t\trandom_other_country = {\n";
		onActionsFile << "\t\t\t\tlimit = {\n";
		onActionsFile << "\t\t\t\t\thas_government = democratic\n";
		onActionsFile << "\t\t\t\t\toriginal_tag = ROOT\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t\tset_politics = {\n";
		onActionsFile << "\t\t\t\t\truling_party = democratic\n";
		onActionsFile << "\t\t\t\t\telections_allowed = yes\n";
		onActionsFile << "\t\t\t\t}\n";
		onActionsFile << "\t\t\t}\n";
		onActionsFile << "\t\t}\n";
		onActionsFile << "\t}\n";
	}

	onActionsFile << "\ton_justifying_wargoal_pulse = {\n";
	onActionsFile << "\t\trandom_events = {\n";
	for (unsigned int i = firstWarJustificationEvent;
		  i < (majorIdeologies.size() * majorIdeologies.size() + numNonIdeologicalEvents + firstWarJustificationEvent);
		  i++)
	{
		onActionsFile << "\t\t\t100 = war_justification." << i << "\n";
	}
	onActionsFile << "\t\t\t17000 = 0\n";
	onActionsFile << "\t\t}\n";
	onActionsFile << "\t}\n";

	onActionsFile << "\ton_startup = {\n";
	onActionsFile << "\t\teffect = {\n";
	onActionsFile << "\t\t\tset_province_name = { id = 587 name = \"K\xC3\xB6ln\"} #Cologne\n";
	onActionsFile << "\t\t\tset_province_name = { id = 957 name = \"Vladivostok\"} #Haishenwai\n";
	onActionsFile << "\t\t\tset_province_name = { id = 1025 name = \"Kokura\"} #Fukuoka\n";
	onActionsFile << "\t\t\tset_province_name = { id = 1047 name = \"Guangzhou\"} #Canton\n";
	onActionsFile << "\t\t\tset_province_name = { id = 1182 name = \"Tokyo\"} #Edo\n";
	onActionsFile << "\t\t\tset_province_name = { id = 1440 name = \"San Juan\"} #Puerto Rico\n";
	onActionsFile << "\t\t\tset_province_name = { id = 1843 name = \"Miami\"} #Tampa\n";
	onActionsFile << "\t\t\tset_province_name = { id = 3151 name = \"Leningrad\"} #Saint Petersburg\n";
	onActionsFile << "\t\t\tset_province_name = { id = 3152 name = \"Tallinn\"} #Reval\n";
	onActionsFile << "\t\t\tset_province_name = { id = 3529 name = \"Stalingrad\"} #Tsaritsyn\n";
	onActionsFile << "\t\t\tset_province_name = { id = 4180 name = \"Honolulu\"} #Hawaii\n";
	onActionsFile << "\t\t\tset_province_name = { id = 4268 name = \"Noum" "\xC3\xA9" "a\"} #New Caledonia\n";
	onActionsFile << "\t\t\tset_province_name = { id = 4333 name = \"Astana\"} #Qaraganda\n";
	onActionsFile << "\t\t\tset_province_name = { id = 4709 name = \"\xC3\x9Cr\xC3\xBCmqi\"} #D\xC3\xADhu\xC3\xA0\n";
	onActionsFile << "\t\t\tset_province_name = { id = 4801 name = \"Ulaanbaatar\"} #Urga\n";
	onActionsFile << "\t\t\tset_province_name = { id = 6115 name = \"Oslo\"} #Christiania\n";
	onActionsFile << "\t\t\tset_province_name = { id = 7371 name = \"Kuching\"} #Brunei\n";
	onActionsFile << "\t\t\tset_province_name = { id = 11437 name = \"Dnipropetrovsk\"} #Ekaterinoslav\n";
	onActionsFile << "\t\t\tset_province_name = { id = 12674 name = \"Reykjavik\"} #Iceland\n";
	for (const auto& [tag, focusId]: onActions.getFocusEvents())
	{
		onActionsFile << "\t\t\t" << tag << " = { country_event = " << focusId << ".1 }\n";
	}
	onActionsFile << "\t\t}\n";
	onActionsFile << "\t}\n";

	onActionsFile << "}\n";

	onActionsFile.close();
}
