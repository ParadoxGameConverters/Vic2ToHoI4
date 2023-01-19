#include "src/HOI4World/Operations/Operations.h"
#include <sstream>



void HoI4::Operations::updateOperations(const std::set<std::string>& majorIdeologies)
{
	for (auto& operation: operations)
	{
		if (operation.getName() == "operation_coup_government")
		{
			updateOperationCoupGovernment(operation, majorIdeologies);
		}
	}
}


void HoI4::Operations::updateOperationCoupGovernment(Operation& operation, const std::set<std::string>& majorIdeologies)
{
	std::stringstream newVisible;
	newVisible << "= {\n";
	newVisible << "\t\tnetwork_strength = {\n";
	newVisible << "\t\t\ttarget = FROM\n";
	newVisible << "\t\t\tvalue > 35\n";
	newVisible << "\t\t}\n";
	newVisible << "\t}";
	operation.setVisible(newVisible.str());

	std::stringstream newAvailable;
	newAvailable << "= {\n";
	newAvailable << "\t\tFROM = {\n";
	newAvailable << "\t\t\thas_civil_war = no\n";
	newAvailable << "\t\t\tNOT = {\n";
	newAvailable << "\t\t\t\thas_government = var:PREV.ROOT.current_party_ideology_group\n";
	newAvailable << "\t\t\t}\n";
	for (const auto& ideology: majorIdeologies)
	{
		newAvailable << "\t\t\tif = {\n";
		newAvailable << "\t\t\t\tlimit = {\n";
		newAvailable << "\t\t\t\t\tPREV.ROOT = { has_government = " << ideology << " }\n";
		newAvailable << "\t\t\t\t}\n";
		newAvailable << "\t\t\t\t" << ideology << " > 0.2\n";
		newAvailable << "\t\t\t}\n";
	}
	newAvailable << "\t\t\t\t#set_temp_variable = { coup_ideology@ROOT = PREV.ROOT.current_party_ideology_group }\n";
	newAvailable
		 << "\t\t\t\t#set_temp_variable = { coup_ideology_popularity@ROOT = party_popularity@ROOT.coup_ideology }\n";
	newAvailable << "\t\t\t\t#check_variable = { ROOT.coup_ideology_popularity > 0.2 }\n";
	newAvailable << "\t\t\t\n";
	newAvailable << "\t\t\tOR = {\n";
	newAvailable << "\t\t\t\tAND = {\n";
	newAvailable << "\t\t\t\t\tis_major = no\n";
	newAvailable << "\t\t\t\t\thas_war = no\n";
	newAvailable << "\t\t\t\t\thas_stability < 0.7 #majors are harder to coup\n";
	newAvailable << "\t\t\t\t}\n";
	newAvailable << "\t\t\t\tAND = {\n";
	newAvailable << "\t\t\t\t\thas_war = no\n";
	newAvailable << "\t\t\t\t\thas_stability < 0.5\n";
	newAvailable << "\t\t\t\t}\n";
	newAvailable << "\t\t\t\thas_stability < 0.35 #can always coup at low stability\n";
	newAvailable << "\t\t\t}\n";
	newAvailable << "\t\t}\n";
	newAvailable << "\t\tOR = {\n";
	newAvailable << "\t\t\thas_game_rule = {\n";
	newAvailable << "\t\t\t\trule = allow_coups\n";
	newAvailable << "\t\t\t\toption = FREE\n";
	newAvailable << "\t\t\t}\n";
	newAvailable << "\t\t\tAND = {\n";
	newAvailable << "\t\t\t\thas_game_rule = {\n";
	newAvailable << "\t\t\t\t\trule = allow_coups\n";
	newAvailable << "\t\t\t\t\toption = AI_ONLY\n";
	newAvailable << "\t\t\t\t}\n";
	newAvailable << "\t\t\t\tFROM = {\n";
	newAvailable << "\t\t\t\t\tis_ai = yes\n";
	newAvailable << "\t\t\t\t}\n";
	newAvailable << "\t\t\t}\n";
	newAvailable << "\t\t}\n";
	newAvailable << "\t}";

	operation.setAvailable(newAvailable.str());
}