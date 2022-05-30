#include "ScriptedEffects.h"
#include "ScriptedEffectFile.h"
#include <sstream>



HoI4::ScriptedEffects::ScriptedEffects(const std::string& HoI4Location):
	 operationStratEffects(
		  ScriptedEffectFile().getScriptedEffects(HoI4Location + "/common/scripted_effects/operation_strat_effects.txt"))
{
}


void HoI4::ScriptedEffects::updateOperationStratEffects(const std::set<std::string>& majorIdeologies)
{
	for (auto& effect: operationStratEffects)
	{
		if (effect.getName() == "update_operation_ai")
		{
			updateUpdateOperationAi(&effect, majorIdeologies);
		}
	}
}


void HoI4::ScriptedEffects::updateUpdateOperationAi(ScriptedEffect* updateOperationAi,
	 const std::set<std::string>& majorIdeologies) const
{
	for (auto& [itemName, itemBody]: updateOperationAi->getMutableItems())
	{
		if (!std::regex_search(itemBody, std::regex("fascism")))
		{
			continue;
		}

		std::stringstream newBody;
		newBody << "= {\n";
		newBody << "\t\t# if found a target pick an operation\n";
		newBody << "\t\tlimit = { \n";
		newBody << "\t\t\tNOT = { check_variable = { generic_operation_target = 0 } }\n";
		newBody << "\t\t\t# if we are already preparing for current one no need to recalc\n";
		newBody << "\t\t\tOR = {\n";
		newBody << "\t\t\t\tcheck_variable = { generic_operation_type_to_run = 0 }\n";
		newBody << "\t\t\t\tNOT = { \n";
		newBody << "\t\t\t\t\tis_preparing_operation = {\n";
		newBody << "\t\t\t\t\t\ttarget = var:generic_operation_target\n";
		newBody << "\t\t\t\t\t\toperation = var:generic_operation_type_to_run\n";
		newBody << "\t\t\t\t\t}\n";
		newBody << "\t\t\t\t}\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t}\n";
		newBody << "\t\t\n";
		newBody << "\t\tif = {\n";
		newBody << "\t\t\tlimit = { \n";
		newBody << "\t\t\t\tnum_of_operatives > min_needed_operative_for_operations\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# these two arrays are filled with operation tokens and corresponding score\n";
		newBody << "\t\t\tclear_temp_array = operation_types\n";
		newBody << "\t\t\tclear_temp_array = operation_types_scores\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# civilian infiltration\n";
		newBody << "\t\t\tset_temp_variable = { score = 100 }\n";
		newBody << "\t\t\tadd_to_temp_array = { operation_types = token:operation_infiltrate_civilian }\n";
		newBody << "\t\t\tadd_to_temp_array = { operation_types_scores = score }\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# army infiltration\n";
		newBody << "\t\t\tset_temp_variable = { score = 50 }\n";
		newBody << "\t\t\tadd_to_temp_variable = { score = num_armies }\n";
		newBody << "\t\t\tclamp_temp_variable = { var = score max = 180 }\n";
		newBody << "\t\t\tadd_to_temp_array = { operation_types = token:operation_infiltrate_armed_forces_army }\n";
		newBody << "\t\t\tadd_to_temp_array = { operation_types_scores = score }\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# air infiltration\n";
		newBody << "\t\t\tset_temp_variable = { score = 50 }\n";
		newBody << "\t\t\tadd_to_temp_variable = { t = num_deployed_planes }\n";
		newBody << "\t\t\tdivide_temp_variable = { t = 10 }\n";
		newBody << "\t\t\tadd_to_temp_variable = { score = t }\n";
		newBody << "\t\t\tclamp_temp_variable = { var = score max = 180 }\n";
		newBody << "\t\t\tadd_to_temp_array = { operation_types = token:operation_infiltrate_armed_forces_airforce }\n";
		newBody << "\t\t\tadd_to_temp_array = { operation_types_scores = score }\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# navy infiltration\n";
		newBody << "\t\t\tvar:generic_operation_target = {\n";
		newBody << "\t\t\t\tif = {\n";
		newBody << "\t\t\t\t\tlimit = { \n";
		newBody << "\t\t\t\t\t\thas_navy_size = { size > 0 } \n";
		newBody << "\t\t\t\t\t\tPREV = {\n";
		newBody << "\t\t\t\t\t\t\thas_navy_size = { size > 0 } \n";
		newBody << "\t\t\t\t\t\t}\n";
		newBody << "\t\t\t\t\t}\n";
		newBody << "\t\t\t\t\tset_temp_variable = { score = num_ships }\n";
		newBody << "\t\t\t\t\t\n";
		newBody << "\t\t\t\t\tset_temp_variable = { t = num_ships_with_type@carrier }\n";
		newBody << "\t\t\t\t\tmultiply_temp_variable = { t = 20 }\n";
		newBody << "\t\t\t\t\tadd_to_temp_variable = { score = t }\n";
		newBody << "\t\t\t\t\t\n";
		newBody << "\t\t\t\t\tset_temp_variable = { t = num_ships_with_type@capital }\n";
		newBody << "\t\t\t\t\tmultiply_temp_variable = { t = 10 }\n";
		newBody << "\t\t\t\t\tadd_to_temp_variable = { score = t }\n";
		newBody << "\t\t\t\t\t\n";
		newBody << "\t\t\t\t\tclamp_temp_variable = { var = score max = 180 }\n";
		newBody << "\t\t\t\t\t\n";
		newBody << "\t\t\t\t\tadd_to_temp_array = { operation_types = token:operation_infiltrate_armed_forces_navy }\n";
		newBody << "\t\t\t\t\tadd_to_temp_array = { operation_types_scores = score }\n";
		newBody << "\t\t\t\t}\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# get token for boost resistance\n";
		newBody << "\t\t\tvar:generic_operation_target = {\n";
		if (majorIdeologies.contains("fascism") && majorIdeologies.contains("absolutist"))
		{
			newBody << "\t\t\t\t# only do on fascist and absolutist\n";
		}
		else if (majorIdeologies.contains("fascism"))
		{
			newBody << "\t\t\t\t# only do on fascist\n";
		}
		else if (majorIdeologies.contains("absolutist"))
		{
			newBody << "\t\t\t\t# only do on absolutist\n";
		}
		if (majorIdeologies.contains("fascism"))
		{
			newBody << "\t\t\t\tif = {\n";
			newBody << "\t\t\t\t\tlimit = { \n";
			newBody << "\t\t\t\t\t\tPREV = {\n";
			newBody << "\t\t\t\t\t\t\tNOT = { has_government = fascism } \n";
			newBody << "\t\t\t\t\t\t\tNOT = {\n";
			newBody << "\t\t\t\t\t\t\t\thas_operation_token = {\n";
			newBody << "\t\t\t\t\t\t\t\t\ttag = var:generic_operation_target\n";
			newBody << "\t\t\t\t\t\t\t\t\ttoken = token_resistance_contacts\n";
			newBody << "\t\t\t\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\thas_government = fascism\n";
			newBody << "\t\t\t\t\t\tcheck_variable = { occupied_countries^num > 0 }\n";
			newBody << "\t\t\t\t\t\thas_added_tension_amount > 20\n";
			newBody << "\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\n";
			newBody << "\t\t\t\t\t# ~number of occupied_states\n";
			newBody << "\t\t\t\t\tset_temp_variable = { t = 1 }\n";
			newBody << "\t\t\t\t\tadd_to_temp_variable = { t = num_controlled_states }\n";
			newBody << "\t\t\t\t\tsubtract_from_temp_variable = { t = num_owned_states }\n";
			newBody << "\t\t\t\t\tclamp_temp_variable = { var = t min = 1 }\n";
			newBody << "\t\t\t\t\t\n";
			newBody << "\t\t\t\t\tset_temp_variable = { score = t }\n";
			newBody << "\t\t\t\t\tmultiply_temp_variable = { score = 15 }\n";
			newBody << "\t\t\t\t\tadd_to_temp_variable = { score = 50 }\n";
			newBody << "\t\t\t\t\tclamp_temp_variable = { var = score max = 200 }\n";
			newBody << "\t\t\t\t\t\n";
			newBody << "\t\t\t\t\tadd_to_temp_array = { operation_types = token:operation_make_resistance_contacts }\n";
			newBody << "\t\t\t\t\tadd_to_temp_array = { operation_types_scores = score }\n";
			newBody << "\t\t\t\t}\n";
		}
		if (majorIdeologies.contains("absolutist"))
		{
			newBody << "\t\t\t\tif = {\n";
			newBody << "\t\t\t\t\tlimit = { \n";
			newBody << "\t\t\t\t\t\tPREV = {\n";
			newBody << "\t\t\t\t\t\t\tNOT = { has_government = absolutist } \n";
			newBody << "\t\t\t\t\t\t\tNOT = {\n";
			newBody << "\t\t\t\t\t\t\t\thas_operation_token = {\n";
			newBody << "\t\t\t\t\t\t\t\t\ttag = var:generic_operation_target\n";
			newBody << "\t\t\t\t\t\t\t\t\ttoken = token_resistance_contacts\n";
			newBody << "\t\t\t\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\thas_government = absolutist\n";
			newBody << "\t\t\t\t\t\tcheck_variable = { occupied_countries^num > 0 }\n";
			newBody << "\t\t\t\t\t\thas_added_tension_amount > 20\n";
			newBody << "\t\t\t\t\t}\n";
			newBody << "\t\t\t\t\t\n";
			newBody << "\t\t\t\t\t# ~number of occupied_states\n";
			newBody << "\t\t\t\t\tset_temp_variable = { t = 1 }\n";
			newBody << "\t\t\t\t\tadd_to_temp_variable = { t = num_controlled_states }\n";
			newBody << "\t\t\t\t\tsubtract_from_temp_variable = { t = num_owned_states }\n";
			newBody << "\t\t\t\t\tclamp_temp_variable = { var = t min = 1 }\n";
			newBody << "\t\t\t\t\t\n";
			newBody << "\t\t\t\t\tset_temp_variable = { score = t }\n";
			newBody << "\t\t\t\t\tmultiply_temp_variable = { score = 15 }\n";
			newBody << "\t\t\t\t\tadd_to_temp_variable = { score = 50 }\n";
			newBody << "\t\t\t\t\tclamp_temp_variable = { var = score max = 200 }\n";
			newBody << "\t\t\t\t\t\n";
			newBody << "\t\t\t\t\tadd_to_temp_array = { operation_types = token:operation_make_resistance_contacts }\n";
			newBody << "\t\t\t\t\tadd_to_temp_array = { operation_types_scores = score }\n";
			newBody << "\t\t\t\t}\n";
		}
		newBody << "\t\t\t}\n";
		newBody << "\t\t\t# boost resistance\n";
		newBody << "\t\t\tif = {\n";
		newBody << "\t\t\t\tlimit = { \n";
		newBody << "\t\t\t\t\thas_operation_token = {\n";
		newBody << "\t\t\t\t\t\ttag = var:generic_operation_target\n";
		newBody << "\t\t\t\t\t\ttoken = token_resistance_contacts\n";
		newBody << "\t\t\t\t\t}\n";
		newBody << "\t\t\t\t}\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t\tadd_to_temp_array = { operation_types = token:operation_boost_resistance }\n";
		newBody << "\t\t\t\tadd_to_temp_array = { operation_types_scores = 1000 }\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\tfor_each_loop = {\n";
		newBody << "\t\t\t\tarray = operation_types\n";
		newBody << "\t\t\t\t\n";
		newBody << "\t\t\t\t# randomization by half\n";
		newBody << "\t\t\t\tset_temp_variable = { t = random }\n";
		newBody << "\t\t\t\tmultiply_temp_variable = { t = 0.5 }\n";
		newBody << "\t\t\t\tadd_to_temp_variable = { t = 0.5 }\n";
		newBody << "\t\t\t\tmultiply_temp_variable = { operation_types_scores^i = t }\n";
		newBody << "\t\t\t\t\n";
		newBody << "\t\t\t\tif = {\n";
		newBody << "\t\t\t\t\tlimit = {\n";
		newBody << "\t\t\t\t\t\tnum_finished_operations = {\n";
		newBody << "\t\t\t\t\t\t\ttarget = var:generic_operation_target\n";
		newBody << "\t\t\t\t\t\t\toperation = var:v\n";
		newBody << "\t\t\t\t\t\t\tvalue > 0\n";
		newBody << "\t\t\t\t\t\t}\n";
		newBody << "\t\t\t\t\t\t\n";
		newBody << "\t\t\t\t\t\t# lower score if we have a finished operation\n";
		newBody << "\t\t\t\t\t\tmultiply_temp_variable = { operation_types_scores^i = 0.5 }\n";
		newBody << "\t\t\t\t\t\t\t\t\n";
		newBody << "\t\t\t\t\t\t# cancel if more than 1 is executed\n";
		newBody << "\t\t\t\t\t\tif = {\n";
		newBody << "\t\t\t\t\t\t\tlimit = {\n";
		newBody << "\t\t\t\t\t\t\t\tnum_finished_operations = {\n";
		newBody << "\t\t\t\t\t\t\t\t\ttarget = var:generic_operation_target\n";
		newBody << "\t\t\t\t\t\t\t\t\toperation = var:v\n";
		newBody << "\t\t\t\t\t\t\t\t\tvalue > 1\n";
		newBody << "\t\t\t\t\t\t\t\t}\n";
		newBody << "\t\t\t\t\t\t\t\t\n";
		newBody << "\t\t\t\t\t\t\t\tset_temp_variable = { operation_types_scores^i = -1 }\n";
		newBody << "\t\t\t\t\t\t\t}\n";
		newBody << "\t\t\t\t\t\t}\n";
		newBody << "\t\t\t\t\t}\n";
		newBody << "\t\t\t\t}\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t\t\n";
		newBody << "\t\t\t# highest score will be selected\n";
		newBody << "\t\t\tfind_highest_in_array = {\n";
		newBody << "\t\t\t\tarray = operation_types_scores\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t\tif = {\n";
		newBody << "\t\t\t\tlimit = { check_variable = { v > 0 } }\n";
		newBody << "\t\t\t\tset_variable = { generic_operation_type_to_run = operation_types^i } # used in ai strat "
					  "generic_operation_ai\n";
		newBody << "\t\t\t}\n";
		newBody << "\t\t}\n";
		newBody << "\t\telse =\n";
		newBody << "\t\t{\n";
		newBody << "\t\t\tset_variable = { generic_operation_type_to_run = 0 }\n";
		newBody << "\t\t}\n";
		newBody << "\t}";
		itemBody = newBody.str();
	}
}