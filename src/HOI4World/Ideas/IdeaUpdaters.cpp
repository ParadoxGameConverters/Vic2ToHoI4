#include "src/HOI4World/Ideas/IdeaUpdaters.h"



void HoI4::updateMobilizationLaws(IdeaGroup& mobilizationLaws, const std::set<std::string>& majorIdeologies)
{
	if (auto serviceByRequirement = mobilizationLaws.getIdea("service_by_requirement"); serviceByRequirement)
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

	if (auto extensiveConscription = mobilizationLaws.getIdea("extensive_conscription"); extensiveConscription)
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
	if (auto warEconomy = economicIdeas.getIdea("war_economy"); warEconomy)
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

	if (auto newEconomicPolicy = economicIdeas.getIdea("new_economic_policy"); newEconomicPolicy)
	{
		auto allowedToRemove = newEconomicPolicy->getAllowedToRemove();
		if (majorIdeologies.contains("communism"))
		{
			allowedToRemove.replace(allowedToRemove.find("$COMMUNISM"), 10, "NOT = { has_government = communism }");
		}
		else
		{
			allowedToRemove.replace(allowedToRemove.find("\t\t\t\t\t$COMMUNISM\n"), 16, "");
		}
		newEconomicPolicy->setAllowedToRemove(allowedToRemove);

		economicIdeas.replaceIdea(*newEconomicPolicy);
	}

	if (auto newEconomicPolicy = economicIdeas.getIdea("new_economic_policy_2"); newEconomicPolicy)
	{
		auto allowedToRemove = newEconomicPolicy->getAllowedToRemove();
		if (majorIdeologies.contains("communism"))
		{
			allowedToRemove.replace(allowedToRemove.find("$COMMUNISM"), 10, "NOT = { has_government = communism }");
		}
		else
		{
			allowedToRemove.replace(allowedToRemove.find("\t\t\t\t\t$COMMUNISM\n"), 16, "");
		}
		newEconomicPolicy->setAllowedToRemove(allowedToRemove);

		economicIdeas.replaceIdea(*newEconomicPolicy);
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
		if (majorIdeologies.contains("democratic"))
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

		std::string aiWillDo = "= {\n";
		aiWillDo += "\t\t\t\tfactor = 1\n";
		aiWillDo += "\n";
		aiWillDo += "\t\t\t\tmodifier = {\n";
		aiWillDo += "\t\t\t\t\tadd = -1\n";
		aiWillDo += "\n";
		aiWillDo += "\t\t\t\t\tis_major = no\n";
		aiWillDo += "\t\t\t\t\tis_in_faction = yes\n";
		aiWillDo += "\t\t\t\t\thas_war = yes\n";
		aiWillDo += "\t\t\t\t}\n";
		aiWillDo += "\n";
		aiWillDo += "\t\t\t\t# minors not at war should want to get the bonuses from free trade\n";
		aiWillDo += "\t\t\t\tmodifier = {\n";
		aiWillDo += "\t\t\t\t\tadd = -1\n";
		aiWillDo += "\n";
		aiWillDo += "\t\t\t\t\tis_major = no\n";
		aiWillDo += "\t\t\t\t\thas_war = no\n";
		aiWillDo += "\t\t\t\t}\n";
		aiWillDo += "\t\t\t\tmodifier = {\n";
		aiWillDo += "\t\t\t\t\tfactor = 200\n";
		if (majorIdeologies.contains("fascism"))
		{
			aiWillDo += "\t\t\t\t\tNOT = { has_government = fascism }\n";
		}
		aiWillDo += "\t\t\t\t\tNOT = { has_idea = closed_economy }\n";
		aiWillDo += "\t\t\t\t\thas_war = yes\n";
		aiWillDo += "\t\t\t\t\tis_major = yes\n";
		aiWillDo += "\t\t\t\t}\n";
		aiWillDo += "\t\t\t\tmodifier = {\n";
		aiWillDo += "\t\t\t\t\tadd = 1500\n";
		aiWillDo += "\n";
		aiWillDo += "\t\t\t\t\t# revert from closed_economy if we have large allies\n";
		aiWillDo += "\t\t\t\t\thas_idea = closed_economy\n";
		aiWillDo += "\t\t\t\t\thas_large_ally_not_pick_closed_economy = yes\n";
		aiWillDo += "\t\t\t\t}\n";
		aiWillDo += "\t\t\t}\n";
		limitedExports->setAiWillDo(aiWillDo);
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

	auto nationalUnification = generalIdeas.getIdea("generic_national_unification");
	if (nationalUnification && majorIdeologies.contains("fascism"))
	{
		std::string cancel = "= {\n";
		cancel += "\t\t\t\tNOT = {\n";
		cancel += "\t\t\t\t\thas_dynamic_modifier = { modifier = revanchism }\n";
		cancel += "\t\t\t\t\thas_dynamic_modifier = { modifier = revanchism_fasc }\n";
		cancel += "\t\t\t\t}\n";
		cancel += "\t\t\t}\n";
		nationalUnification->updateCancel(cancel);
		generalIdeas.replaceIdea(*nationalUnification);
	}

	auto colonialElite = generalIdeas.getIdea("ENG_colonial_elite");
	if (colonialElite && majorIdeologies.contains("communism"))
	{
		std::string allowedCivilWar = "= {\n";
		allowedCivilWar += "\t\t\t\tNOT = {\n";
		allowedCivilWar += "\t\t\t\t\thas_government = communism\n";
		allowedCivilWar += "\t\t\t\t}\n";
		allowedCivilWar += "\t\t\t}";
		colonialElite->setAllowedCivilWar(allowedCivilWar);
		generalIdeas.replaceIdea(*colonialElite);
	}

	auto indianIndependencePromised = generalIdeas.getIdea("indian_independence_promised_idea");
	if (indianIndependencePromised && majorIdeologies.contains("democratic"))
	{
		std::string allowedCivilWar = "= {\n";
		allowedCivilWar += "\t\t\t\thas_government = democratic\n";
		allowedCivilWar += "\t\t\t}";
		indianIndependencePromised->setAllowedCivilWar(allowedCivilWar);
		generalIdeas.replaceIdea(*indianIndependencePromised);
	}
}


void HoI4::updateNeutralIdeas(IdeaGroup& neutralIdeas, const std::set<std::string>& majorIdeologies)
{
	auto collectivistEthosFocusNeutral = neutralIdeas.getIdea("collectivist_ethos_focus_neutral");
	if (majorIdeologies.contains("democratic"))
	{
		collectivistEthosFocusNeutral->setAllowedCivilWar(
			 "= {\n"
			 "\t\t\t\tAND = {\n"
			 "\t\t\t\t\tNOT = { has_government = democratic }\n"
			 "\t\t\t\t\tNOT = { has_government = neutrality }\n"
			 "\t\t\t\t}\n"
			 "\t\t\t}");
	}
	else
	{
		collectivistEthosFocusNeutral->setAllowedCivilWar(
			 "= {\n"
			 "\t\t\t\tNOT = { has_government = neutrality }\n"
			 "\t\t\t}");
	}
	neutralIdeas.replaceIdea(*collectivistEthosFocusNeutral);

	auto libertyEthosFocusNeutral = neutralIdeas.getIdea("liberty_ethos_focus_neutral");
	if (majorIdeologies.contains("democratic"))
	{
		libertyEthosFocusNeutral->setAllowedCivilWar(
			 "= {\n"
			 "\t\t\t\thas_government = democratic\n"
			 "\t\t\t}");
	}
	neutralIdeas.replaceIdea(*libertyEthosFocusNeutral);
}

void HoI4::updateHiddenIdeas(IdeaGroup& generalIdeas, const std::set<std::string>& majorIdeologies)
{
	auto reclaimCores = generalIdeas.getIdea("reclaim_cores_idea");
	if (reclaimCores && majorIdeologies.contains("fascism"))
	{
		std::string cancel = "= {\n";
		cancel += "\t\t\t\tNOT = {\n";
		cancel += "\t\t\t\t\thas_dynamic_modifier = { modifier = revanchism }\n";
		cancel += "\t\t\t\t\thas_dynamic_modifier = { modifier = revanchism_fasc }\n";
		cancel += "\t\t\t\t}\n";
		cancel += "\t\t\t}\n";
		reclaimCores->updateCancel(cancel);
		generalIdeas.replaceIdea(*reclaimCores);
	}
}