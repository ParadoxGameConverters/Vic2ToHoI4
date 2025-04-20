#include "src/OutHoi4/ScriptedEffects/OutScriptedEffects.h"
#include "src/OutHoi4/ScriptedEffects/OutScriptedEffect.h"
#include <fstream>



void outputGetBestAllianceMatchIdeologyEffects(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}

		output << "\n";
		output << "get_best_alliance_match_" << ideology
				 << "_effect = { #arguably a trigger, but it does stuff so we keep it in here. If this is your first time "
					 "seeing this, welcome to my personal hell.\n";
		output << "\tif = {\n";
		output << "\t\tlimit = {\n";
		output << "\t\t\tany_other_country = {\n";
		output << "\t\t\t\tis_faction_leader = yes\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\thas_government = " << ideology << "\n";
		output << "\t\t\t\tnot = { has_war_with = ROOT }\n";
		output << "\t\t\t\tset_temp_variable = { ROOT.best_leader = this }\n";
		output << "\t\t\t\tset_temp_variable = { ROOT.best_leader_score = 0 }\n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}\n";
		output << "\tif = {\n";
		output << "\t\tlimit = {\n";
		output << "\t\t\tall_other_country = {\n";
		output << "\t\t\t\tis_faction_leader = yes\n";
		output << "\t\t\t\tis_major = yes\n";
		output << "\t\t\t\thas_government = " << ideology << "\n";
		output << "\t\t\t\tnot = { has_war_with = ROOT }\n";
		output << "\t\t\t\tset_temp_variable = { this.leader_score = num_of_factories }\n";
		output << "\t\t\t\tadd_to_temp_variable = { this.leader_score = num_battalions }\n";
		output << "\t\t\t\tall_of_scopes = {\n";
		output << "\t\t\t\t\tarray = allies\n";
		output << "\t\t\t\t\tadd_to_temp_variable = { PREV.leader_score = num_of_factories }\n";
		output << "\t\t\t\t\tadd_to_temp_variable = { PREV.leader_score = num_battalions }\n";
		output << "\t\t\t\t}\n";
		output << "\t\t\t\tif = {\n";
		output << "\t\t\t\t\tlimit = {\n";
		output << "\t\t\t\t\t\tcapital_scope = {\n";
		output << "\t\t\t\t\t\t\tis_on_continent = ROOT\n";
		output << "\t\t\t\t\t\t}\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tmultiply_temp_variable = { leader_score = 2 }\n";
		output << "\t\t\t\t}\n";
		output << "\t\t\t\tif = {\n";
		output << "\t\t\t\t\tlimit = {\n";
		output << "\t\t\t\t\t\tany_neighbor_country = { tag = ROOT }\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t\tmultiply_temp_variable = { leader_score = 1.25 }\n";
		output << "\t\t\t\t}\n";
		output << "\t\t\t\tif = {\n";
		output << "\t\t\t\t\tlimit = {\n";
		output << "\t\t\t\t\t\tcheck_variable = { ROOT.best_leader_score < leader_score }\n";
		output << "\t\t\t\t\t\tset_temp_variable = { ROOT.best_leader = this }\n";
		output << "\t\t\t\t\t\tset_temp_variable = { ROOT.best_leader_score = leader_score }\n";
		output << "\t\t\t\t\t}\n";
		output << "\t\t\t\t}\n";
		output << "\t\t\t}\n";
		output << "\t\t}\n";
		output << "\t}\n";
		output << "}\n";
	}
}


void outputRemoveFromAllowedParty(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	output << "remove_from_allowed_party = {\n";
	auto firstIdeology = true;
	for (const auto& ideology: majorIdeologies)
	{
		if (firstIdeology)
		{
			output << "\tif = {\n";
			firstIdeology = false;
		}
		else
		{
			output << "\telse_if = {\n";
		}
		output << "\t\tlimit = { has_government = " << ideology << " }\n";
		output << "\t\tset_temp_variable = { allowed_party_" << ideology << " = 0 }\n";
		output << "\t}\n";
	}
	output << "}\n";
}

void outputGlobalPlatonicCountries(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	output << "find_global_platonic_countries = { # Look for the countries that meet the best criteria for the "
				 "different platonic countries we expect in HoI \n";
	if (majorIdeologies.contains("fascist"))
	{
		output << "\tfind_biggest_fascist = yes\n";
		output << "\tfind_biggest_fascist_bully = yes\n";
		output << "\tfind_local_dangerous_fascist = yes \n";
	}
	if (majorIdeologies.contains("democratic"))
	{
		output << "\tfind_biggest_democrat = yes\n";
		output << "\tfind_best_democratic_ally_leader = yes\n";
		output << "\tfind_democratic_sleeping_giant = yes\n";
	}
	if (majorIdeologies.contains("communist"))
	{
		output << "\tfind_biggest_communist = yes\n";
	}
	output << "\tfind_biggest_non_aligned = yes\n";
	output << "}\n";
	output << "\n";
	output << "\n";
	if (majorIdeologies.contains("fascist"))
	{
		output << "find_biggest_fascist_bully = { # Finds the biggest and/or meanest fascist country \n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = GLOBAL.platonic_fascist_bully\n";
		output << "\t\tscorer = fascist_bully_scorer\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
		output << "find_biggest_fascist = { # Finds Nazi Germany, or the closest to it \n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = GLOBAL.platonic_big_fascist\n";
		output << "\t\tscorer = fascist_major_scorer\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
		output << "find_local_dangerous_fascist = {\n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = platonic_local_dangerous_fascist\n";
		output << "\t\tscorer = local_fascist_country\n";
		output << "\t}\n";
		output << "}\n";
	}
	if (majorIdeologies.contains("democratic"))
	{
		output << "find_best_democratic_ally_leader = { # Finds the most suitable democratic country to lead a faction\n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = GLOBAL.platonic_democratic_ally_leader\n";
		output << "\t\tscorer = democratic_faction_leader_scorer\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
		output << "find_democratic_sleeping_giant = { # Finds biggest desarmed democratic nation. Expected to be USA \n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = GLOBAL.platonic_democratic_sleeping_giant\n";
		output << "\t\tscorer = democratic_sleeping_giant_scorer\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
		output << "find_biggest_democrat = { # Finds biggest Democratic Nation\n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = GLOBAL.platonic_big_democratic\n";
		output << "\t\tscorer = democratic_major_scorer\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
	}
	if (majorIdeologies.contains("communist"))
	{
		output << "find_biggest_communist = { # Finds biggest Communist\n";
		output << "\tget_highest_scored_country = {\n";
		output << "\t\tvar = GLOBAL.platonic_big_communist\n";
		output << "\t\tscorer = communist_major_scorer\n";
		output << "\t}\n";
		output << "}\n";
		output << "\n";
	}
	output << "find_biggest_non_aligned = { # Finds biggest... anything else\n";
	output << "\tget_highest_scored_country = {\n";
	output << "\t\tvar = GLOBAL.platonic_big_non_aligned\n";
	output << "\t\tscorer = non_aligned_major_scorer\n";
	output << "\t}\n";
	output << "}\n";
	output << "# There are ideology scorers for each continent. If you need more check the generic_platonic_scorers "
				 "file and make a new scripted effect \n";
	output << "\n";
}

void outputRestoreIdeologyPopularities(const std::set<std::string>& majorIdeologies, std::ostream& output)
{
	const std::map<std::string, std::string> ideologyNameMap = {{"fascism", "fascist"},
		 {"communism", "communist"},
		 {"democratic", "democratic"},
		 {"neutrality", "neutrality"},
		 {"absolutist", "absolutist"},
		 {"radical", "radical"}};

	output << "get_current_ideology_popularities = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		output << "\tset_variable = { ROOT." << ideologyNameMap.at(ideology)
				 << "_support_before_change = ROOT.party_popularity_100@" << ideology << " }\n";
	}
	output << "}\n";
	output << "restore_ideology_popularities = {\n";
	output << "\thidden_effect = {\n";
	output << "\t\t# Reset popluarities to what they were before puppeting \n";
	output << "\t\tset_popularities = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		output << "\t\t\t" << ideology << " = ROOT." << ideologyNameMap.at(ideology) << "_support_before_change\n";
	}
	output << "\t\t}\n";
	for (const auto& ideology: majorIdeologies)
	{
		output << "\t\tclear_variable = ROOT." << ideologyNameMap.at(ideology) << "_support_before_change\n";
	}
	output << "\t}\n";
	output << "}\n";
	output << "\n";
}



void HoI4::outputScriptedEffects(const ScriptedEffects& scriptedEffects,
	 const std::set<std::string>& majorIdeologies,
	 const std::filesystem::path& outputName)
{
	const std::filesystem::path strategic_effects_filename =
		 "output" / outputName / "common/scripted_effects/operation_strat_effects.txt";
	std::ofstream operationStratEffects(strategic_effects_filename);
	if (!operationStratEffects.is_open())
	{
		throw std::runtime_error("Could not open " + strategic_effects_filename.string());
	}
	for (const auto& effect: scriptedEffects.getOperationStratEffects())
	{
		operationStratEffects << effect << "\n";
	}

	const std::filesystem::path scripted_effects_file =
		 "output" / outputName / "common/scripted_effects/00_scripted_effects.txt";
	std::ofstream scriptedEffectsFile(scripted_effects_file, std::ios::app);
	if (!scriptedEffectsFile.is_open())
	{
		throw std::runtime_error("Could not open " + scripted_effects_file.string());
	}

	outputGetBestAllianceMatchIdeologyEffects(majorIdeologies, scriptedEffectsFile);
	outputRemoveFromAllowedParty(majorIdeologies, scriptedEffectsFile);
	outputGlobalPlatonicCountries(majorIdeologies, scriptedEffectsFile);
	outputRestoreIdeologyPopularities(majorIdeologies, scriptedEffectsFile);

	scriptedEffectsFile.close();
}