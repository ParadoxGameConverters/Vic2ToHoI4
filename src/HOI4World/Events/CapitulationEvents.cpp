#include "src/HOI4World/Events/CapitulationEvents.h"
#include <sstream>



void updateCapitulationEvent(HoI4::Event& theEvent, const std::set<std::string>& majorIdeologies)
{
	theEvent.clearDescriptions();

	std::stringstream positiveCollaborationDifferentIdeology;
	positiveCollaborationDifferentIdeology << "= {\n";
	positiveCollaborationDifferentIdeology << "\t\ttext = country_capitulated.0.d_positive_collab_diff_ideology\n";
	positiveCollaborationDifferentIdeology << "\t\ttrigger = {\n";
	positiveCollaborationDifferentIdeology << "\t\t\tNOT = { tag = ROOT }\n";
	positiveCollaborationDifferentIdeology << "\t\t\tNOT = {\n";
	positiveCollaborationDifferentIdeology << "\t\t\t\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		positiveCollaborationDifferentIdeology << "\t\t\t\t\tAND = {\n";
		positiveCollaborationDifferentIdeology << "\t\t\t\t\t\tROOT = { has_government = " << ideology << " }\n";
		positiveCollaborationDifferentIdeology << "\t\t\t\t\t\tFROM.FROM = { has_government = " << ideology << " }\n";
		positiveCollaborationDifferentIdeology << "\t\t\t\t\t}\n";
	}
	positiveCollaborationDifferentIdeology << "\t\t\t\t}\n";
	positiveCollaborationDifferentIdeology << "\t\t\t}\n";
	positiveCollaborationDifferentIdeology << "\t\t\tFROM.FROM = {\n";
	positiveCollaborationDifferentIdeology << "\t\t\t\thas_collaboration = {\n";
	positiveCollaborationDifferentIdeology << "\t\t\t\t\ttarget = ROOT\n";
	positiveCollaborationDifferentIdeology << "\t\t\t\t\tvalue > 0.6\n";
	positiveCollaborationDifferentIdeology << "\t\t\t\t}\n";
	positiveCollaborationDifferentIdeology << "\t\t\t}\n";
	positiveCollaborationDifferentIdeology << "\t\t}\n";
	positiveCollaborationDifferentIdeology << "\t}\n";
	theEvent.giveDescription(positiveCollaborationDifferentIdeology.str());

	std::stringstream positiveCollaborationInvadedSameIdeology;
	positiveCollaborationInvadedSameIdeology << "= {\n";
	positiveCollaborationInvadedSameIdeology
		 << "\t\ttext = country_capitulated.0.d_positive_collab_invaded_same_ideology\n";
	positiveCollaborationInvadedSameIdeology << "\t\ttrigger = {\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		if (ideology == "neutrality")
		{
			continue;
		}
		positiveCollaborationInvadedSameIdeology << "\t\t\t\tAND = {\n";
		positiveCollaborationInvadedSameIdeology << "\t\t\t\t\tROOT = { has_government = " << ideology << " }\n";
		positiveCollaborationInvadedSameIdeology << "\t\t\t\t\tFROM.FROM = { has_government = " << ideology << " }\n";
		positiveCollaborationInvadedSameIdeology << "\t\t\t\t}\n";
	}
	positiveCollaborationInvadedSameIdeology << "\t\t\t}\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\tFROM.FROM = {\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\t\thas_collaboration = {\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\t\t\ttarget = ROOT\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\t\t\tvalue > 0.6\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\t\t}\n";
	positiveCollaborationInvadedSameIdeology << "\t\t\t}\n";
	positiveCollaborationInvadedSameIdeology << "\t\t}\n";
	positiveCollaborationInvadedSameIdeology << "\t}\n";
	theEvent.giveDescription(positiveCollaborationInvadedSameIdeology.str());

	std::stringstream positiveBothNoFaction;
	positiveBothNoFaction << "= {\n";
	positiveBothNoFaction << "\t\ttext = country_capitulated.0.d_positive_both_no_faction\n";
	positiveBothNoFaction << "\t\ttrigger = {\n";
	positiveBothNoFaction << "\t\t\tOR = {\n";
	positiveBothNoFaction << "\t\t\t\thas_war_with = ROOT\n";
	positiveBothNoFaction << "\t\t\t\tany_allied_country = { has_war_with = ROOT }\n";
	positiveBothNoFaction << "\t\t\t}\n";
	positiveBothNoFaction << "\t\t\tNOT = {\n";
	positiveBothNoFaction << "\t\t\t\tFROM.FROM = {\n";
	positiveBothNoFaction << "\t\t\t\t\thas_collaboration = {\n";
	positiveBothNoFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	positiveBothNoFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	positiveBothNoFaction << "\t\t\t\t\t}\n";
	positiveBothNoFaction << "\t\t\t\t}\n";
	positiveBothNoFaction << "\t\t\t}\n";
	positiveBothNoFaction << "\t\t\tROOT = { is_in_faction = no }\n";
	positiveBothNoFaction << "\t\t\tFROM = { FROM = { NOT = { any_allied_country = { has_war_with = ROOT } } } }\n";
	positiveBothNoFaction << "\t\t}\n";
	positiveBothNoFaction << "\t}\n";
	theEvent.giveDescription(positiveBothNoFaction.str());

	std::stringstream positivePrevNoFaction;
	positivePrevNoFaction << "= {\n";
	positivePrevNoFaction << "\t\ttext = country_capitulated.0.d_positive_prev_no_faction\n";
	positivePrevNoFaction << "\t\ttrigger = {\n";
	positivePrevNoFaction << "\t\t\tOR = {\n";
	positivePrevNoFaction << "\t\t\t\thas_war_with = ROOT\n";
	positivePrevNoFaction << "\t\t\t\tany_allied_country = { has_war_with = ROOT }\n";
	positivePrevNoFaction << "\t\t\t}\n";
	positivePrevNoFaction << "\t\t\tNOT = {\n";
	positivePrevNoFaction << "\t\t\t\tFROM.FROM = {\n";
	positivePrevNoFaction << "\t\t\t\t\thas_collaboration = {\n";
	positivePrevNoFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	positivePrevNoFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	positivePrevNoFaction << "\t\t\t\t\t}\n";
	positivePrevNoFaction << "\t\t\t\t}\n";
	positivePrevNoFaction << "\t\t\t}\n";
	positivePrevNoFaction << "\t\t\tROOT = { is_in_faction = yes }\n";
	positivePrevNoFaction << "\t\t\tFROM = { FROM = { NOT = { any_allied_country = { has_war_with = ROOT } } } }\n";
	positivePrevNoFaction << "\t\t}\n";
	positivePrevNoFaction << "\t}\n";
	theEvent.giveDescription(positivePrevNoFaction.str());

	std::stringstream positivePrevFaction;
	positivePrevFaction << "= {\n";
	positivePrevFaction << "\t\ttext = country_capitulated.0.d_positive_prev_faction\n";
	positivePrevFaction << "\t\ttrigger = {\n";
	positivePrevFaction << "\t\t\tOR = {\n";
	positivePrevFaction << "\t\t\t\thas_war_with = ROOT\n";
	positivePrevFaction << "\t\t\t\tany_allied_country = { has_war_with = ROOT }\n";
	positivePrevFaction << "\t\t\t}\n";
	positivePrevFaction << "\t\t\tNOT = {\n";
	positivePrevFaction << "\t\t\t\tFROM.FROM = {\n";
	positivePrevFaction << "\t\t\t\t\thas_collaboration = {\n";
	positivePrevFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	positivePrevFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	positivePrevFaction << "\t\t\t\t\t}\n";
	positivePrevFaction << "\t\t\t\t}\n";
	positivePrevFaction << "\t\t\t}\n";
	positivePrevFaction << "\t\t\tROOT = { is_in_faction = yes }\n";
	positivePrevFaction << "\t\t\tFROM = { FROM = { any_allied_country = { has_war_with = ROOT } } }\n";
	positivePrevFaction << "\t\t}\n";
	positivePrevFaction << "\t}\n";
	theEvent.giveDescription(positivePrevFaction.str());

	std::stringstream negativeCollaborationDifferentIdeology;
	negativeCollaborationDifferentIdeology << "= {\n";
	negativeCollaborationDifferentIdeology << "\t\ttext = country_capitulated.0.d_negative_collab_diff_ideology\n";
	negativeCollaborationDifferentIdeology << "\t\ttrigger = {\n";
	negativeCollaborationDifferentIdeology << "\t\t\ttag = ROOT\n";
	negativeCollaborationDifferentIdeology << "\t\t\tNOT = {\n";
	negativeCollaborationDifferentIdeology << "\t\t\t\tOR = {\n";
	for (const auto& ideology: majorIdeologies)
	{
		negativeCollaborationDifferentIdeology << "\t\t\t\t\tAND = {\n";
		negativeCollaborationDifferentIdeology << "\t\t\t\t\t\tROOT = { has_government = " << ideology << " }\n";
		negativeCollaborationDifferentIdeology << "\t\t\t\t\t\tFROM.FROM = { has_government = " << ideology << " }\n";
		negativeCollaborationDifferentIdeology << "\t\t\t\t\t}\n";
	}
	negativeCollaborationDifferentIdeology << "\t\t\t\t}\n";
	negativeCollaborationDifferentIdeology << "\t\t\t}\n";
	negativeCollaborationDifferentIdeology << "\t\t\tFROM.FROM = {\n";
	negativeCollaborationDifferentIdeology << "\t\t\t\thas_collaboration = {\n";
	negativeCollaborationDifferentIdeology << "\t\t\t\t\ttarget = ROOT\n";
	negativeCollaborationDifferentIdeology << "\t\t\t\t\tvalue > 0.6\n";
	negativeCollaborationDifferentIdeology << "\t\t\t\t}\n";
	negativeCollaborationDifferentIdeology << "\t\t\t}\n";
	negativeCollaborationDifferentIdeology << "\t\t}\n";
	negativeCollaborationDifferentIdeology << "\t}\n";
	theEvent.giveDescription(negativeCollaborationDifferentIdeology.str());

	std::stringstream negativeBothNoFaction;
	negativeBothNoFaction << "= {\n";
	negativeBothNoFaction << "\t\ttext = country_capitulated.0.d_negative_both_no_faction\n";
	negativeBothNoFaction << "\t\ttrigger = {\n";
	negativeBothNoFaction << "\t\t\tOR = {\n";
	negativeBothNoFaction << "\t\t\t\thas_war_together_with = ROOT\n";
	negativeBothNoFaction << "\t\t\t\tis_in_faction_with = ROOT\n";
	negativeBothNoFaction << "\t\t\t\ttag = ROOT\n";
	negativeBothNoFaction << "\t\t\t}\n";
	negativeBothNoFaction << "\t\t\tNOT = {\n";
	negativeBothNoFaction << "\t\t\t\tFROM.FROM = {\n";
	negativeBothNoFaction << "\t\t\t\t\thas_collaboration = {\n";
	negativeBothNoFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	negativeBothNoFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	negativeBothNoFaction << "\t\t\t\t\t}\n";
	negativeBothNoFaction << "\t\t\t\t}\n";
	negativeBothNoFaction << "\t\t\t}\n";
	negativeBothNoFaction << "\t\t\tROOT = { is_in_faction = no }\n";
	negativeBothNoFaction << "\t\t\tFROM = { FROM = { NOT = { any_allied_country = { has_war_with = ROOT } } } }\n";
	negativeBothNoFaction << "\t\t}\n";
	negativeBothNoFaction << "\t}\n";
	theEvent.giveDescription(negativeBothNoFaction.str());

	std::stringstream negativePrevNoFaction;
	negativePrevNoFaction << "= {\n";
	negativePrevNoFaction << "\t\ttext = country_capitulated.0.d_negative_prev_no_faction\n";
	negativePrevNoFaction << "\t\ttrigger = {\n";
	negativePrevNoFaction << "\t\t\tOR = {\n";
	negativePrevNoFaction << "\t\t\t\tis_in_faction_with = ROOT\n";
	negativePrevNoFaction << "\t\t\t\ttag = ROOT\n";
	negativePrevNoFaction << "\t\t\t}\n";
	negativePrevNoFaction << "\t\t\tNOT = {\n";
	negativePrevNoFaction << "\t\t\t\tFROM.FROM = {\n";
	negativePrevNoFaction << "\t\t\t\t\thas_collaboration = {\n";
	negativePrevNoFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	negativePrevNoFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	negativePrevNoFaction << "\t\t\t\t\t}\n";
	negativePrevNoFaction << "\t\t\t\t}\n";
	negativePrevNoFaction << "\t\t\t}\n";
	negativePrevNoFaction << "\t\t\tROOT = { is_in_faction = yes }\n";
	negativePrevNoFaction << "\t\t\tFROM = { FROM = { NOT = { any_allied_country = { has_war_with = ROOT } } } }\n";
	negativePrevNoFaction << "\t\t}\n";
	negativePrevNoFaction << "\t}\n";
	theEvent.giveDescription(negativePrevNoFaction.str());

	std::stringstream negativePrevFaction;
	negativePrevFaction << "= {\n";
	negativePrevFaction << "\t\ttext = country_capitulated.0.d_negative_prev_faction\n";
	negativePrevFaction << "\t\ttrigger = {\n";
	negativePrevFaction << "\t\t\tOR = {\n";
	negativePrevFaction << "\t\t\t\tis_in_faction_with = ROOT\n";
	negativePrevFaction << "\t\t\t\ttag = ROOT\n";
	negativePrevFaction << "\t\t\t}\n";
	negativePrevFaction << "\t\t\tNOT = {\n";
	negativePrevFaction << "\t\t\t\tFROM.FROM = {\n";
	negativePrevFaction << "\t\t\t\t\thas_collaboration = {\n";
	negativePrevFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	negativePrevFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	negativePrevFaction << "\t\t\t\t\t}\n";
	negativePrevFaction << "\t\t\t\t}\n";
	negativePrevFaction << "\t\t\t}\n";
	negativePrevFaction << "\t\t\tROOT = { is_in_faction = yes }\n";
	negativePrevFaction << "\t\t\tFROM = { FROM = { any_allied_country = { has_war_with = ROOT } } }\n";
	negativePrevFaction << "\t\t}\n";
	negativePrevFaction << "\t}\n";
	theEvent.giveDescription(negativePrevFaction.str());

	std::stringstream neutralBothNoFaction;
	neutralBothNoFaction << "= {\n";
	neutralBothNoFaction << "\t\ttext = country_capitulated.0.d_neutral_both_no_faction\n";
	neutralBothNoFaction << "\t\ttrigger = {\n";
	neutralBothNoFaction << "\t\t\tNOT = { has_war_together_with = ROOT }\n";
	neutralBothNoFaction << "\t\t\tNOT = { is_in_faction_with = ROOT }\n";
	neutralBothNoFaction << "\t\t\tNOT = { has_war_with = ROOT }\n";
	neutralBothNoFaction << "\t\t\tNOT = { any_allied_country = { has_war_with = ROOT } }\n";
	neutralBothNoFaction << "\t\t\tROOT = { is_in_faction = no }\n";
	neutralBothNoFaction << "\t\t\tNOT = {\n";
	neutralBothNoFaction << "\t\t\t\tFROM.FROM = {\n";
	neutralBothNoFaction << "\t\t\t\t\thas_collaboration = {\n";
	neutralBothNoFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	neutralBothNoFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	neutralBothNoFaction << "\t\t\t\t\t}\n";
	neutralBothNoFaction << "\t\t\t\t}\n";
	neutralBothNoFaction << "\t\t\t}\n";
	neutralBothNoFaction << "\t\t\tFROM = { FROM = { NOT = { any_allied_country = { has_war_with = ROOT } } } }\n";
	neutralBothNoFaction << "\t\t}\n";
	neutralBothNoFaction << "\t}\n";
	theEvent.giveDescription(neutralBothNoFaction.str());

	std::stringstream neutralPrevNoFaction;
	neutralPrevNoFaction << "= {\n";
	neutralPrevNoFaction << "\t\ttext = country_capitulated.0.d_neutral_prev_no_faction\n";
	neutralPrevNoFaction << "\t\ttrigger = {\n";
	neutralPrevNoFaction << "\t\t\tNOT = { is_in_faction_with = ROOT }\n";
	neutralPrevNoFaction << "\t\t\tNOT = { has_war_with = ROOT }\n";
	neutralPrevNoFaction << "\t\t\tNOT = { any_allied_country = { has_war_with = ROOT } }\n";
	neutralPrevNoFaction << "\t\t\tROOT = { is_in_faction = yes }\n";
	neutralPrevNoFaction << "\t\t\tNOT = {\n";
	neutralPrevNoFaction << "\t\t\t\tFROM.FROM = {\n";
	neutralPrevNoFaction << "\t\t\t\t\thas_collaboration = {\n";
	neutralPrevNoFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	neutralPrevNoFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	neutralPrevNoFaction << "\t\t\t\t\t}\n";
	neutralPrevNoFaction << "\t\t\t\t}\n";
	neutralPrevNoFaction << "\t\t\t}\n";
	neutralPrevNoFaction << "\t\t\tFROM = { FROM = { NOT = { any_allied_country = { has_war_with = ROOT } } } }\n";
	neutralPrevNoFaction << "\t\t}\n";
	neutralPrevNoFaction << "\t}\n";
	theEvent.giveDescription(neutralPrevNoFaction.str());

	std::stringstream neutralPrevFaction;
	neutralPrevFaction << "= {\n";
	neutralPrevFaction << "\t\ttext = country_capitulated.0.d_neutral_prev_faction\n";
	neutralPrevFaction << "\t\ttrigger = {\n";
	neutralPrevFaction << "\t\t\tNOT = { is_in_faction_with = ROOT }\n";
	neutralPrevFaction << "\t\t\tNOT = { has_war_with = ROOT }\n";
	neutralPrevFaction << "\t\t\tNOT = { any_allied_country = { has_war_with = ROOT } }\n";
	neutralPrevFaction << "\t\t\tROOT = { is_in_faction = yes }\n";
	neutralPrevFaction << "\t\t\tNOT = {\n";
	neutralPrevFaction << "\t\t\t\tFROM.FROM = {\n";
	neutralPrevFaction << "\t\t\t\t\thas_collaboration = {\n";
	neutralPrevFaction << "\t\t\t\t\t\ttarget = ROOT\n";
	neutralPrevFaction << "\t\t\t\t\t\tvalue > 0.6\n";
	neutralPrevFaction << "\t\t\t\t\t}\n";
	neutralPrevFaction << "\t\t\t\t}\n";
	neutralPrevFaction << "\t\t\t}\n";
	neutralPrevFaction << "\t\t\tFROM = { FROM = { any_allied_country = { has_war_with = ROOT } } }\n";
	neutralPrevFaction << "\t\t}\n";
	neutralPrevFaction << "\t}\n";
	theEvent.giveDescription(neutralPrevFaction.str());

	theEvent.clearOptions();

	HoI4::EventOption optionA;
	optionA.giveName("country_capitulated.0.a");
	optionA.giveTrigger(
		 "OR = {\n"
		 "\t\t\t\tany_allied_country = {\n"
		 "\t\t\t\t\thas_war_with = ROOT\n"
		 "\t\t\t\t}\n"
		 "\t\t\t\thas_war_with = ROOT\n"
		 "\t\t\t}");
	theEvent.giveOption(std::move(optionA));

	HoI4::EventOption optionB;
	optionB.giveName("country_capitulated.0.b");
	optionB.giveTrigger(
		 "OR = {\n"
		 "\t\t\t\thas_war_together_with = ROOT\n"
		 "\t\t\t\tis_in_faction_with = ROOT\n"
		 "\t\t\t\ttag = ROOT\n"
		 "\t\t\t}");
	theEvent.giveOption(std::move(optionB));

	HoI4::EventOption optionC;
	optionC.giveName("country_capitulated.0.c");
	optionC.giveTrigger(
		 "NOT = { has_war_together_with = ROOT }\n"
		 "\t\t\tNOT = { is_in_faction_with = ROOT }\n"
		 "\t\t\tNOT = { any_allied_country = { has_war_with = ROOT } }\n"
		 "\t\t\tNOT = { has_war_with = ROOT }\n"
		 "\t\t\tNOT = { tag = ROOT }");
	theEvent.giveOption(std::move(optionC));
}