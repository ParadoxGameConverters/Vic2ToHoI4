#include "src/HOI4World/Decisions/NavalTreatyDecisions.h"
#include <sstream>



void HoI4::NavalTreatyDecisions::updateDecisions(const std::set<std::string>& majorIdeologies,
	 const std::vector<std::string>& strongestGpNavies)
{
	if (strongestGpNavies.empty())
	{
		decisions.clear();
		return;
	}

	for (auto& decisionsCategory: decisions)
	{
		for (auto decision: decisionsCategory.getDecisions())
		{
			if ((decision.getName() == "MTG_abandon_treaty_democratic") && !majorIdeologies.contains("democratic"))
			{
				std::string newVisible = "= {\n";
				newVisible += "\t\t\thas_naval_treaty_trigger = yes\n";
				newVisible += "\t\t\tOR = {\n";
				newVisible += "\t\t\t\thas_government = neutrality\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);
				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_abandon_treaty_fascist")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 1\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newVisible = "= {\n";
				newVisible += "\t\t\thas_naval_treaty_trigger = yes\n";
				newVisible += "\t\t\tOR = { \n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					newVisible += "\t\t\t\thas_government = " + ideology + "\n";
				}
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_cheat_on_treaty")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 3\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newVisible = "= {\n";
				newVisible += "\t\t\tOR = {\n";
				newVisible += "\t\t\t\thas_idea = MTG_naval_treaty_adherent\n";
				newVisible += "\t\t\t\thas_idea = MTG_naval_treaty_adherent_reduced\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t\tOR = {\n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					newVisible += "\t\t\t\thas_government = " + ideology + "\n";
				}
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_invite_FROM_to_treaty")
			{
				std::stringstream newTargetTrigger;
				newTargetTrigger << "= {\n";
				newTargetTrigger << "\t\t\tFROM = { \n";
				newTargetTrigger << "\t\t\t\thas_war = no\n";
				newTargetTrigger << "\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger << "\t\t\t\tNOT = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger << "\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger << "\t\t\t\tif = {\n";
				newTargetTrigger << "\t\t\t\t\tlimit = { " << *strongestGpNavies.begin()
									  << " = { has_naval_treaty_trigger = yes } }\n";
				newTargetTrigger << "\t\t\t\t\tnaval_strength_comparison = {\n";
				newTargetTrigger << "\t\t\t\t\t\tother = " << *strongestGpNavies.begin() << "\n";
				newTargetTrigger << "\t\t\t\t\t\tratio > 0.35\n";
				newTargetTrigger << "\t\t\t\t\t\tsub_unit_def_weights = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\tcarrier = 0.25\n";
				newTargetTrigger << "\t\t\t\t\t\t\tbattleship = 1\n";
				newTargetTrigger << "\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
				newTargetTrigger << "\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
				newTargetTrigger << "\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t}\n";
				for (int i = 1; i < strongestGpNavies.size(); i++)
				{
					newTargetTrigger << "\t\t\t\telse_if = {\n";
					newTargetTrigger << "\t\t\t\t\tlimit = { " << strongestGpNavies[i]
										  << " = { has_naval_treaty_trigger = yes } }\n";
					newTargetTrigger << "\t\t\t\t\tnaval_strength_comparison = {\n";
					newTargetTrigger << "\t\t\t\t\t\tother = " << strongestGpNavies[i] << "\n";
					newTargetTrigger << "\t\t\t\t\t\tratio > 0.35\n";
					newTargetTrigger << "\t\t\t\t\t\tsub_unit_def_weights = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\tcarrier = 0.25\n";
					newTargetTrigger << "\t\t\t\t\t\t\tbattleship = 1\n";
					newTargetTrigger << "\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
					newTargetTrigger << "\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
					newTargetTrigger << "\t\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t}\n";
				}
				newTargetTrigger << "\t\t\t\telse = {\n";
				newTargetTrigger << "\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger << "\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger << "\t\t\t\t\t\tsize > 15\n";
				newTargetTrigger << "\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t}\n";
				newTargetTrigger << "\t\t}";
				decision.setTargetTrigger(newTargetTrigger.str());

				std::string newAiWillDo = "= {\n";
				newAiWillDo += "\t\t\tfactor = 0\n";
				newAiWillDo += "\t\t\tmodifier = {\n";
				newAiWillDo += "\t\t\t\tOR = {\n";
				for (const auto& tag: strongestGpNavies)
				{
					newAiWillDo += "\t\t\t\t\tTAG = " + tag + "\n";
				}
				newAiWillDo += "\t\t\t\t}\n";
				newAiWillDo += "\t\t\t\tOR = {\n";
				if (majorIdeologies.contains("democratic"))
				{
					newAiWillDo += "\t\t\t\t\thas_government = democratic\n";
				}
				newAiWillDo += "\t\t\t\t\thas_government = neutrality\n";
				newAiWillDo += "\t\t\t\t}\n";
				newAiWillDo += "\t\t\t\tadd = 10\n";
				newAiWillDo += "\t\t\t}\n";
				newAiWillDo += "\t\t}";
				decision.setAiWillDo(newAiWillDo);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM_previous_signatory")
			{
				std::stringstream newTargetTrigger;
				newTargetTrigger << "= {\n";
				newTargetTrigger << "\t\t\tFROM = { \n";
				newTargetTrigger << "\t\t\t\thas_war = no\n";
				newTargetTrigger << "\t\t\t\thas_country_flag = MTG_naval_treaty_abandoned\n";
				newTargetTrigger << "\t\t\t\tif = {\n";
				newTargetTrigger << "\t\t\t\t\tlimit = { " << *strongestGpNavies.begin()
									  << " = { has_naval_treaty_trigger = yes } }\n";
				newTargetTrigger << "\t\t\t\t\tnaval_strength_comparison = {\n";
				newTargetTrigger << "\t\t\t\t\t\tother = " << *strongestGpNavies.begin() << "\n";
				newTargetTrigger << "\t\t\t\t\t\tratio > 0.8\n";
				newTargetTrigger << "\t\t\t\t\t\tsub_unit_def_weights = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\tcarrier = 0.25\n";
				newTargetTrigger << "\t\t\t\t\t\t\tbattleship = 1\n";
				newTargetTrigger << "\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
				newTargetTrigger << "\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
				newTargetTrigger << "\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t}\n";
				for (int i = 1; i < strongestGpNavies.size(); i++)
				{
					newTargetTrigger << "\t\t\t\telse_if = {\n";
					newTargetTrigger << "\t\t\t\t\tlimit = { " << strongestGpNavies[i]
										  << " = { has_naval_treaty_trigger = yes } }\n";
					newTargetTrigger << "\t\t\t\t\tnaval_strength_comparison = {\n";
					newTargetTrigger << "\t\t\t\t\t\tother = " << strongestGpNavies[i] << "\n";
					newTargetTrigger << "\t\t\t\t\t\tratio > 0.8\n";
					newTargetTrigger << "\t\t\t\t\t\tsub_unit_def_weights = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\tcarrier = 0.25\n";
					newTargetTrigger << "\t\t\t\t\t\t\tbattleship = 1\n";
					newTargetTrigger << "\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
					newTargetTrigger << "\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
					newTargetTrigger << "\t\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t}\n";
				}
				newTargetTrigger << "\t\t\t\telse = {\n";
				newTargetTrigger << "\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger << "\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger << "\t\t\t\t\t\tsize > 20\n";
				newTargetTrigger << "\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t}\n";
				newTargetTrigger << "\t\t}";
				decision.setTargetTrigger(newTargetTrigger.str());

				std::string newAiWillDo = "= {\n";
				newAiWillDo += "\t\t\tfactor = 10\n";
				newAiWillDo += "\t\t\tmodifier = {\n";
				newAiWillDo += "\t\t\t\tNOT = {\n";
				newAiWillDo += "\t\t\t\t\tOR = {\n";
				for (const auto& tag: strongestGpNavies)
				{
					newAiWillDo += "\t\t\t\t\tTAG = " + tag + "\n";
				}
				newAiWillDo += "\t\t\t\t\t}\n";
				newAiWillDo += "\t\t\t\t}\n";
				newAiWillDo += "\t\t\t\tfactor = 0\n";
				newAiWillDo += "\t\t\t}\n";
				newAiWillDo += "\t\t}";
				decision.setAiWillDo(newAiWillDo);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM")
			{
				std::stringstream newTargetTrigger;
				newTargetTrigger << "= {\n";
				newTargetTrigger << "\t\t\tFROM = {\n";
				newTargetTrigger << "\t\t\t\tOR = {\n";
				newTargetTrigger << "\t\t\t\t\tAND = {\n";
				newTargetTrigger << "\t\t\t\t\t\thas_war = no\n";
				newTargetTrigger << "\t\t\t\t\t\tnot = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger << "\t\t\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger << "\t\t\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger << "\t\t\t\t\t\tif = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\tlimit = { " << *strongestGpNavies.begin()
									  << " = { has_naval_treaty_trigger = yes } }\n";
				newTargetTrigger << "\t\t\t\t\t\t\tnaval_strength_comparison = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tother = " << *strongestGpNavies.begin() << "\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tratio > 1\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tsub_unit_def_weights = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\tcarrier = 0.5\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattleship = 1\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t\t}\n";
				for (int i = 1; i < strongestGpNavies.size(); i++)
				{
					newTargetTrigger << "\t\t\t\t\t\telse_if = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\tlimit = { " << strongestGpNavies[i]
										  << " = { has_naval_treaty_trigger = yes } }\n";
					newTargetTrigger << "\t\t\t\t\t\t\tnaval_strength_comparison = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\tother = " << strongestGpNavies[i] << "\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\tratio > 1\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\tsub_unit_def_weights = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\tcarrier = 0.5\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattleship = 1\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t\t\t}\n";
				}
				newTargetTrigger << "\t\t\t\t\t\telse = { \n";
				newTargetTrigger << "\t\t\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger << "\t\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\tAND = {\n";
				newTargetTrigger << "\t\t\t\t\t\thas_naval_treaty_trigger = yes\n";
				newTargetTrigger << "\t\t\t\t\t\tif = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\tlimit = { " << *strongestGpNavies.begin()
									  << " = { has_naval_treaty_trigger = yes } }\n";
				newTargetTrigger << "\t\t\t\t\t\t\tnaval_strength_comparison = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tother = " << *strongestGpNavies.begin() << "\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tratio > 1.1\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tsub_unit_def_weights = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\tcarrier = 0.5\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattleship = 1\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t\t}\n";
				for (int i = 1; i < strongestGpNavies.size(); i++)
				{
					newTargetTrigger << "\t\t\t\t\t\telse_if = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\tlimit = { " << strongestGpNavies[i]
										  << " = { has_naval_treaty_trigger = yes } }\n";
					newTargetTrigger << "\t\t\t\t\t\t\tnaval_strength_comparison = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\tother = " << strongestGpNavies[i] << "\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\tratio > 1.1\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\tsub_unit_def_weights = {\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\tcarrier = 0.5\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattleship = 1\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\tbattle_cruiser = 0.8\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t\theavy_cruiser = 0.5\n";
					newTargetTrigger << "\t\t\t\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t\t\t\t}\n";
					newTargetTrigger << "\t\t\t\t\t\t}\n";
				}
				newTargetTrigger << "\t\t\t\t\t\telse = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger << "\t\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger << "\t\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t\t}\n";
				newTargetTrigger << "\t\t\t}\n";
				newTargetTrigger << "\t\t}";
				decision.setTargetTrigger(newTargetTrigger.str());

				std::string newAiWillDo = "= {\n";
				newAiWillDo += "\t\t\tfactor = 10\n";
				newAiWillDo += "\t\t\tmodifier = {\n";
				newAiWillDo += "\t\t\t\tNOT = {\n";
				newAiWillDo += "\t\t\t\t\tOR = {\n";
				for (const auto& tag: strongestGpNavies)
				{
					newAiWillDo += "\t\t\t\t\tTAG = " + tag + "\n";
				}
				newAiWillDo += "\t\t\t\t\t}\n";
				newAiWillDo += "\t\t\t\t}\n";
				newAiWillDo += "\t\t\t\tfactor = 0\n";
				newAiWillDo += "\t\t\t}\n";
				newAiWillDo += "\t\t}";
				decision.setAiWillDo(newAiWillDo);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\tif = {\n";
				newAvailable +=
					 "\t\t\t\tlimit = { " + *strongestGpNavies.begin() + " = { has_naval_treaty_trigger = yes } }\n";
				newAvailable += "\t\t\t\tnaval_strength_comparison = {\n";
				newAvailable += "\t\t\t\t\tother = " + *strongestGpNavies.begin() + "\n";
				newAvailable += "\t\t\t\t\tratio < 0.8\n";
				newAvailable += "\t\t\t\t\tsub_unit_def_weights = {\n";
				newAvailable += "\t\t\t\t\t\tcarrier = 0.25\n";
				newAvailable += "\t\t\t\t\t\tbattleship = 1\n";
				newAvailable += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
				newAvailable += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
				newAvailable += "\t\t\t\t\t}\n";
				newAvailable += "\t\t\t\t}\n";
				newAvailable += "\t\t\t}\n";
				for (int i = 1; i < strongestGpNavies.size(); i++)
				{
					newAvailable += "\t\t\telse_if = {\n";
					newAvailable +=
						 "\t\t\t\tlimit = { " + strongestGpNavies[i] + " = { has_naval_treaty_trigger = yes } }\n";
					newAvailable += "\t\t\t\tnaval_strength_comparison = {\n";
					newAvailable += "\t\t\t\t\tother = " + strongestGpNavies[i] + "\n";
					newAvailable += "\t\t\t\t\tratio < 0.8\n";
					newAvailable += "\t\t\t\t\tsub_unit_def_weights = {\n";
					newAvailable += "\t\t\t\t\t\tcarrier = 0.25\n";
					newAvailable += "\t\t\t\t\t\tbattleship = 1\n";
					newAvailable += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
					newAvailable += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
					newAvailable += "\t\t\t\t\t}\n";
					newAvailable += "\t\t\t\t}\n";
					newAvailable += "\t\t\t}\n";
				}
				newAvailable += "\t\t\telse = {\n";
				newAvailable += "\t\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\t\tsize < 20\n";
				newAvailable += "\t\t\t\t}\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_signatory_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\tif = {\n";
				newAvailable +=
					 "\t\t\t\tlimit = { " + *strongestGpNavies.begin() + " = { has_naval_treaty_trigger = yes } }\n";
				newAvailable += "\t\t\t\tnaval_strength_comparison = {\n";
				newAvailable += "\t\t\t\t\tother = " + *strongestGpNavies.begin() + "\n";
				newAvailable += "\t\t\t\t\tratio < 1\n";
				newAvailable += "\t\t\t\t\tsub_unit_def_weights = {\n";
				newAvailable += "\t\t\t\t\t\tcarrier = 0.5\n";
				newAvailable += "\t\t\t\t\t\tbattleship = 1\n";
				newAvailable += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
				newAvailable += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
				newAvailable += "\t\t\t\t\t}\n";
				newAvailable += "\t\t\t\t}\n";
				newAvailable += "\t\t\t}\n";
				for (int i = 1; i < strongestGpNavies.size(); i++)
				{
					newAvailable += "\t\t\telse_if = {\n";
					newAvailable +=
						 "\t\t\t\tlimit = { " + strongestGpNavies[i] + " = { has_naval_treaty_trigger = yes } }\n";
					newAvailable += "\t\t\t\tnaval_strength_comparison = {\n";
					newAvailable += "\t\t\t\t\tother = " + strongestGpNavies[i] + "\n";
					newAvailable += "\t\t\t\t\tratio < 1\n";
					newAvailable += "\t\t\t\t\tsub_unit_def_weights = {\n";
					newAvailable += "\t\t\t\t\t\tcarrier = 0.5\n";
					newAvailable += "\t\t\t\t\t\tbattleship = 1\n";
					newAvailable += "\t\t\t\t\t\tbattle_cruiser = 0.8\n";
					newAvailable += "\t\t\t\t\t\theavy_cruiser = 0.5\n";
					newAvailable += "\t\t\t\t\t}\n";
					newAvailable += "\t\t\t\t}\n";
					newAvailable += "\t\t\t}\n";
				}
				newAvailable += "\t\t\telse = {\n";
				newAvailable += "\t\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\t\tsize < 50\n";
				newAvailable += "\t\t\t\t}\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
		}
	}
}