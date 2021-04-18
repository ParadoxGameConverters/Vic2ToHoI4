#include "NavalTreatyDecisions.h"



void HoI4::NavalTreatyDecisions::updateDecisions(const std::set<std::string>& majorIdeologies)
{
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
				std::string newAiWillDo = "= {\n\t\t\tfactor = 0\n\t\t}";
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
				std::string newAiWillDo = "= {\n";
				newAiWillDo += "\t\t\tfactor = 3\n";
				if (majorIdeologies.contains("democratic"))
				{
					newAiWillDo += "\t\t\tmodifier = {\n";
					newAiWillDo += "\t\t\t\thas_government = democratic\n";
					newAiWillDo += "\t\t\t\tadd = 10\n";
					newAiWillDo += "\t\t\t}\n";
				}
				newAiWillDo += "\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = { \n";
				newTargetTrigger += "\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger += "\t\t\t\tNOT = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger += "\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger += "\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\tsize > 15\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM_previous_signatory")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 10\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = { \n";
				newTargetTrigger += "\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\thas_country_flag = MTG_naval_treaty_abandoned\n";
				newTargetTrigger += "\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\tsize > 20\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 10\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = {\n";
				newTargetTrigger += "\t\t\t\tOR = {\n";
				newTargetTrigger += "\t\t\t\t\tAND = {\n";
				newTargetTrigger += "\t\t\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\t\t\tnot = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger += "\t\t\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger += "\t\t\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger += "\t\t\t\t\t\thas_navy_size = { \n";
				newTargetTrigger += "\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger += "\t\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\tAND = {\n";
				newTargetTrigger += "\t\t\t\t\t\thas_naval_treaty_trigger = yes\n";
				newTargetTrigger += "\t\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger += "\t\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\tsize < 20\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_signatory_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\tsize < 50\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
		}
	}
}