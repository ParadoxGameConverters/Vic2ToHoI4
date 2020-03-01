#include "IdeaUpdaters.h"



void HoI4::updateMobilizationLaws(IdeaGroup& mobilizationLaws, const std::set<std::string>& majorIdeologies)
{
	auto serviceByRequirement = mobilizationLaws.getIdea("service_by_requirement");
	if (serviceByRequirement)
	{
		std::string available = "= {\n";
		available += "\t\t\t\t#has_manpower_for_recruit_change_to =  { value = 0.1 group = mobilization_laws }\n";
		available += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				available += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		available += "\t\t\t\t\tAND = {\n";
		available += "\t\t\t\t\t\thas_war = yes\n";
		available += "\t\t\t\t\t\tenemies_strength_ratio > 0.6\n";
		available += "\t\t\t\t\t\t#any_enemy_country = {\n";
		available += "\t\t\t\t\t\t#\tstrength_ratio = {\n";
		available += "\t\t\t\t\t\t#\t\ttag = ROOT \n";
		available += "\t\t\t\t\t\t#\t\tratio > 0.6\n";
		available += "\t\t\t\t\t\t#\t}\n";
		available += "\t\t\t\t\t\t#}\n";
		available += "\t\t\t\t\t}\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t\tOR = {\n";
		available += "\t\t\t\t\thas_war_support > 0.6\n";
		available += "\t\t\t\t\tsurrender_progress > 0\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t}";
		serviceByRequirement->setAvailable(available);
		mobilizationLaws.replaceIdea(*serviceByRequirement);
	}

	auto extensiveConscription = mobilizationLaws.getIdea("extensive_conscription");
	if (extensiveConscription)
	{
		std::string available = "= {\n";
		available += "\t\t\t\t#has_manpower_for_recruit_change_to = { value = 0.05 group = mobilization_laws }\n";
		available += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				available += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		available += "\t\t\t\t\tAND = {\n";
		available += "\t\t\t\t\t\thas_war = yes\n";
		available += "\t\t\t\t\t\tenemies_strength_ratio > 0.5\n";
		available += "\t\t\t\t\t\t#any_enemy_country = {\n";
		available += "\t\t\t\t\t\t#\tstrength_ratio = {\n";
		available += "\t\t\t\t\t\t#\t\ttag = ROOT \n";
		available += "\t\t\t\t\t\t#\t\tratio > 0.5\n";
		available += "\t\t\t\t\t\t#\t}\n";
		available += "\t\t\t\t\t\t#}\n";
		available += "\t\t\t\t\t}\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t\thas_war_support > 0.2\n";
		available += "\t\t\t}";
		extensiveConscription->setAvailable(available);
		mobilizationLaws.replaceIdea(*extensiveConscription);
	}
}


void HoI4::updateEconomyIdeas(IdeaGroup& economicIdeas, const std::set<std::string>& majorIdeologies)
{
	auto warEconomy = economicIdeas.getIdea("war_economy");
	if (warEconomy)
	{
		std::string available = "= {\n";
		available += "\t\t\t\thas_war_support > 0.5\n";
		available += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				available += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		available += "\t\t\t\t\tcustom_trigger_tooltip = { tooltip = or_clarification_tooltip always = no }\n";
		available += "\t\t\t\t\tAND = {\n";
		available += "\t\t\t\t\t\thas_war = yes\n";
		available += "\t\t\t\t\t\tany_enemy_country = {\n";
		available += "\t\t\t\t\t\t\tic_ratio = { \n";
		available += "\t\t\t\t\t\t\t\ttag = ROOT \n";
		available += "\t\t\t\t\t\t\t\tratio > 0.4\n";
		available += "\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t}\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t}";
		warEconomy->setAvailable(available);
		economicIdeas.replaceIdea(*warEconomy);
	}
}


void HoI4::updateTradeLaws(IdeaGroup& tradeLaws, const std::set<std::string>& majorIdeologies)
{
	auto closedEconomy = tradeLaws.getIdea("closed_economy");
	if (closedEconomy)
	{
		std::string available = "= {\n";
		available += "\t\t\t\thas_war = yes\n";
		available += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				available += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		available += "\t\t\t\t}\n";
		available += "\t\t\t\tOR = {\n";
		available += "\t\t\t\t\thas_idea = war_economy\n";
		available += "\t\t\t\t\thas_idea = tot_economic_mobilisation\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t}";
		closedEconomy->setAvailable(available);
		tradeLaws.replaceIdea(*closedEconomy);
	}

	auto limitedExports = tradeLaws.getIdea("limited_exports");
	if (limitedExports)
	{
		std::string available = "= {\n";
		if (majorIdeologies.count("democratic") > 0)
		{
			available += "\t\t\t\tOR = {\n";
			available += "\t\t\t\t\tAND = {\n";
			available += "\t\t\t\t\t\thas_government = democratic\n";
			available += "\t\t\t\t\t\thas_war = yes\n";
			available += "\t\t\t\t\t\tany_enemy_country = {\n";
			available += "\t\t\t\t\t\t\tic_ratio = { \n";
			available += "\t\t\t\t\t\t\t\ttag = ROOT \n";
			available += "\t\t\t\t\t\t\t\tratio > 0.2\n";
			available += "\t\t\t\t\t\t\t}\n";
			available += "\t\t\t\t\t\t}\n";
			available += "\t\t\t\t\t}\n";
			available += "\t\t\t\t\tAND = {\n";
			available += "\t\t\t\t\t\tNOT = { has_government = democratic }\n";
			available += "\t\t\t\t\t\tOR = {\n";
			available += "\t\t\t\t\t\t\thas_idea = partial_economic_mobilisation\n";
			available += "\t\t\t\t\t\t\thas_idea = war_economy\n";
			available += "\t\t\t\t\t\t\thas_idea = tot_economic_mobilisation\n";
			available += "\t\t\t\t\t\t}\n";
			available += "\t\t\t\t\t}\n";
			available += "\t\t\t\t}\n";
		}
		else
		{
			available += "\t\t\t\tOR = {\n";
			available += "\t\t\t\t\thas_idea = partial_economic_mobilisation\n";
			available += "\t\t\t\t\thas_idea = war_economy\n";
			available += "\t\t\t\t\thas_idea = tot_economic_mobilisation\n";
			available += "\t\t\t\t}\n";
		}
		available += "\t\t\t}";
		limitedExports->setAvailable(available);
		tradeLaws.replaceIdea(*limitedExports);
	}
}


void HoI4::updateGeneralIdeas(IdeaGroup& generalIdeas, const std::set<std::string>& majorIdeologies)
{
	auto militaryYouthFocus = generalIdeas.getIdea("military_youth_focus");
	if (militaryYouthFocus)
	{
		std::string allowedCivilWar = "= {\n";
		allowedCivilWar += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				allowedCivilWar += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		allowedCivilWar += "\t\t\t\t}\n";
		allowedCivilWar += "\t\t\t}";
		militaryYouthFocus->setAllowedCivilWar(allowedCivilWar);
		generalIdeas.replaceIdea(*militaryYouthFocus);
	}

	auto paramilitarismFocus = generalIdeas.getIdea("paramilitarism_focus");
	if (paramilitarismFocus)
	{
		std::string allowedCivilWar = "= {\n";
		allowedCivilWar += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				allowedCivilWar += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		allowedCivilWar += "\t\t\t\t}\n";
		allowedCivilWar += "\t\t\t}";
		paramilitarismFocus->setAllowedCivilWar(allowedCivilWar);
		generalIdeas.replaceIdea(*paramilitarismFocus);
	}

	auto indoctrinationFocus = generalIdeas.getIdea("indoctrination_focus");
	if (indoctrinationFocus)
	{
		std::string allowedCivilWar = "= {\n";
		allowedCivilWar += "\t\t\t\tOR = {\n";
		for (const auto& ideology: majorIdeologies)
		{
			if ((ideology != "neutrality") && (ideology != "democratic"))
			{
				allowedCivilWar += "\t\t\t\t\thas_government = " + ideology + "\n";
			}
		}
		allowedCivilWar += "\t\t\t\t}\n";
		allowedCivilWar += "\t\t\t}";
		indoctrinationFocus->setAllowedCivilWar(allowedCivilWar);
		generalIdeas.replaceIdea(*indoctrinationFocus);
	}
}