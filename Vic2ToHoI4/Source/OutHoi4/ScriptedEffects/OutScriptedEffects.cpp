#include "OutScriptedEffects.h"
#include "OutScriptedEffect.h"
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



void HoI4::outputScriptedEffects(const ScriptedEffects& scriptedEffects,
	 const std::set<std::string>& majorIdeologies,
	 const std::string& outputName)
{
	std::ofstream operationStratEffects("output/" + outputName + "/common/scripted_effects/operation_strat_effects.txt");
	if (!operationStratEffects.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + outputName + "/common/scripted_effects/operation_strat_effects.txt");
	}
	for (const auto& effect: scriptedEffects.getOperationStratEffects())
	{
		operationStratEffects << effect << "\n";
	}

	std::ofstream scriptedEffectsFile("output/" + outputName + "/common/scripted_effects/00_scripted_effects.txt",
		 std::ios::app);
	if (!scriptedEffectsFile.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + outputName + "/common/scripted_effects/00_scripted_effects.txt");
	}

	outputGetBestAllianceMatchIdeologyEffects(majorIdeologies, scriptedEffectsFile);
	outputRemoveFromAllowedParty(majorIdeologies, scriptedEffectsFile);

	scriptedEffectsFile.close();
}