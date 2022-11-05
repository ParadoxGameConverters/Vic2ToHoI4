#include "src/HOI4World/PeaceConferences/DynamicAiPeaces.h"
#include <sstream>



std::vector<std::string> HoI4::GenerateDynamicAiPeaces(const std::set<std::string>& major_ideologies)
{
	std::vector<std::string> dynamic_ai_peaces;

	std::stringstream dont_puppet_and_force_government;
	dont_puppet_and_force_government << "\tdont_puppet_and_force_government = {\n";
	dont_puppet_and_force_government << "\t\tpeace_action_type = { puppet }\n";
	dont_puppet_and_force_government << "\n";
	dont_puppet_and_force_government << "\t\tenable = {\n";
	dont_puppet_and_force_government << "\t\t\tif = {\n";
	dont_puppet_and_force_government << "\t\t\t\tlimit = { has_government = neutrality }\n";
	dont_puppet_and_force_government << "\t\t\t\tROOT.FROM.FROM = { pc_is_forced_government_to = neutrality }\n";
	dont_puppet_and_force_government << "\t\t\t}\n";
	for (const auto& major_ideology: major_ideologies)
	{
		dont_puppet_and_force_government << "\t\t\telse_if = {\n";
		dont_puppet_and_force_government << "\t\t\t\tlimit = { has_government = " << major_ideology << " }\n";
		dont_puppet_and_force_government << "\t\t\t\tROOT.FROM.FROM = { pc_is_forced_government_to = " << major_ideology
													<< " }\n";
		dont_puppet_and_force_government << "\t\t\t}\n";
	}
	dont_puppet_and_force_government << "\t\t\telse = {\n";
	dont_puppet_and_force_government << "\t\t\t\talways = no\n";
	dont_puppet_and_force_government << "\t\t\t}\n";
	dont_puppet_and_force_government << "\t\t}\n";
	dont_puppet_and_force_government << "\t\tai_desire = -200\n";
	dont_puppet_and_force_government << "\t}\n";
	dynamic_ai_peaces.push_back(dont_puppet_and_force_government.str());

	std::stringstream do_force_government_if_forced_to_our_ideology;
	do_force_government_if_forced_to_our_ideology << "\tdo_force_government_if_forced_to_our_ideology = {\n";
	do_force_government_if_forced_to_our_ideology << "\t\tpeace_action_type = { force_government }\n";
	do_force_government_if_forced_to_our_ideology << "\n";
	do_force_government_if_forced_to_our_ideology << "\t\tenable = {\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\tif = {\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t\tlimit = { has_government = neutrality }\n";
	do_force_government_if_forced_to_our_ideology
		 << "\t\t\t\tROOT.FROM.FROM = { pc_is_forced_government_to = neutrality }\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t}\n";
	for (const auto& major_ideology: major_ideologies)
	{
		do_force_government_if_forced_to_our_ideology << "\t\t\telse_if = {\n";
		do_force_government_if_forced_to_our_ideology << "\t\t\t\tlimit = { has_government = " << major_ideology
																	 << " }\n";
		do_force_government_if_forced_to_our_ideology
			 << "\t\t\t\tROOT.FROM.FROM = { pc_is_forced_government_to = " << major_ideology << " }\n";
		do_force_government_if_forced_to_our_ideology << "\t\t\t}\n";
	}
	do_force_government_if_forced_to_our_ideology << "\t\t\telse_if = {\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t\tlimit = { has_government = fascism }\n";
	do_force_government_if_forced_to_our_ideology
		 << "\t\t\t\tROOT.FROM.FROM = { pc_is_forced_government_to = fascism }\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t}\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\telse_if = {\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t\tlimit = { has_government = communism }\n";
	do_force_government_if_forced_to_our_ideology
		 << "\t\t\t\tROOT.FROM.FROM = { pc_is_forced_government_to = communism }\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t}\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\telse = {\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t\talways = no\n";
	do_force_government_if_forced_to_our_ideology << "\t\t\t}\n";
	do_force_government_if_forced_to_our_ideology << "\t\t}\n";
	do_force_government_if_forced_to_our_ideology << "\t\tai_desire = 20\n";
	do_force_government_if_forced_to_our_ideology << "\t}\n";
	dynamic_ai_peaces.push_back(do_force_government_if_forced_to_our_ideology.str());

	return dynamic_ai_peaces;
}
