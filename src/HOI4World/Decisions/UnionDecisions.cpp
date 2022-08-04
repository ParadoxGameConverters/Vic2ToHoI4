#include "src/HOI4World/Decisions/UnionDecisions.h"

void HoI4::UnionDecisions::createDecisions(const std::vector<HoI4::UnionCountry>& unionCountries)
{
	DecisionsInCategory formable_decisions_category("formable_nations");
	for (auto unionCountry: unionCountries)
	{
		const auto& oldTag = unionCountry.GetOldTag();
		const auto& tag = unionCountry.GetTag();
		const auto& name = "form_" + tag;
		decision formationDecisionStateTrigger(name + "_state_trigger");
		decision formationDecision(name);

		// STATE TRIGGER
		// Allowed
		std::string allowed = "= {\n";
		allowed += "\t\t\tNOT = { original_tag = " + oldTag + " }\n";
		allowed += "\t\t}\n";
		formationDecisionStateTrigger.setAllowed(allowed);

		// State Target/On Map Mode/Icon
		formationDecisionStateTrigger.setStateTarget(true);
		formationDecisionStateTrigger.setOnMapMode("map_only");
		formationDecisionStateTrigger.setIcon("decision_generic_nationalism");

		// Target ROOT Trigger
		std::string targetRootTrigger = "= {\n";
		targetRootTrigger += "\t\t\t highlight_states_trigger = {\n";
		targetRootTrigger += "\t\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			targetRootTrigger += "\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		targetRootTrigger += "\t\t\t\t}\n";
		targetRootTrigger += "\t\t\t\tNOT = { is_controlled_by = ROOT }\n";
		targetRootTrigger += "\t\t\t}\n";
		targetRootTrigger += "\t\t}\n";
		formationDecisionStateTrigger.setTargetTrigger(targetRootTrigger);

		// Target Trigger
		std::string targetTrigger = "= {\n";
		targetTrigger += "\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			targetTrigger += "\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		targetTrigger += "\t\t\t}\n";
		targetTrigger += "\t\t\tNOT = { is_controlled_by = ROOT }\n";
		targetTrigger += "\t\t}\n";
		formationDecisionStateTrigger.setTargetTrigger(targetTrigger);

		// Highlight States
		std::string highlightStates = "= {\n";
		highlightStates += "\t\t\t highlight_states_trigger = {\n";
		highlightStates += "\t\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			highlightStates += "\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		highlightStates += "\t\t\t\t}\n";
		highlightStates += "\t\t\t\tNOT = { is_controlled_by = ROOT }\n";
		highlightStates += "\t\t\t}\n";
		highlightStates += "\t\t\thighlight_color_before_active = 1\n";
		highlightStates += "\t\t\thighlight_color_while_active = 2\n";
		highlightStates += "\t\t}\n";
		formationDecisionStateTrigger.setHighlightStateTargets(highlightStates);

		// Available
		std::string available = "= {\n";
		available += "\t\t\t hidden_trigger = {\n";
		available += "\t\t\t\t set_temp_variable = { temp_original_states = 0 }\n";
		available += "\t\t\t\t set_temp_variable = { original_states = 0 }\n";
		available += "\t\t\t\t all_state = {\n";
		available += "\t\t\t\t\t if = {\n";
		available += "\t\t\t\t\t\t limit = {\n";
		available += "\t\t\t\t\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			available += "\t\t\t\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		available += "\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\tadd_to_temp_variable = { ROOT.original_states = 1 }\n";
		available += "\t\t\t\t\t}\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t\tall_controlled_state = {\n";
		available += "\t\t\t\t\t if = {\n";
		available += "\t\t\t\t\t\t limit = {\n";
		available += "\t\t\t\t\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			available += "\t\t\t\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		available += "\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\tadd_to_temp_variable = { ROOT.temp_original_states = 1 }\n";
		available += "\t\t\t\t\t}\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t\tmultiply_temp_variable = { ROOT.original_states = 0.75 }\n";
		available += "\t\t\t\tround_temp_variable = ROOT.original_states\n";
		available += "\t\t\t}\n";
		available += "\t\t\tcustom_trigger_tooltip = {\n";
		available += "\t\t\t\ttooltip = union_formation_decision_tt\n";
		available += "\t\t\t\tcheck_variable = {\n";
		available += "\t\t\t\t\tvar = temp_original_states\n";
		available += "\t\t\t\t\tvalue = original_states\n";
		available += "\t\t\t\t\tcompare = greater_than_or_equals\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t}\n";
		available += "\t\t\tNOT = {\n";
		available += "\t\t\t\tany_other_country = {\n";
		available += "\t\t\t\t\thas_cosmetic_tag = CHI_union\n";
		available += "\t\t\t\t\texists = yes\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t}\n";
		available += "\t\t}\n";
		formationDecisionStateTrigger.setAvailable(available);

		// Complete Effect
		std::string completeEffect = "= {\n";
		completeEffect += "\t\t\tactivate_decision = " + name + "\n";
		completeEffect += "\t\t}";
		formationDecisionStateTrigger.setCompleteEffect(completeEffect);

		// AI Will Do
		formationDecisionStateTrigger.setAiWillDo("= {\n\t\t\tbase = 100\n\t\t}");

		// Add to Category
		formable_decisions_category.addDecision(formationDecisionStateTrigger);


		// FORMATION DECISION
		// Allowed
		formationDecision.setAllowed(allowed); // Same as State Trigger

		// Visible
		std::string visible = "= {\n";
		visible += "\t\t\tOR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			visible += "\t\t\t\thas_idea = culture_" + culture + "\n";
		}
		visible += "\t\t\t}\n";
		visible += "\t\t\t" + oldTag + " = { exists = no }\n";
		visible += "\t\t}\n";
		formationDecision.setVisible(visible);

		// Available
		formationDecision.setAvailable(available); // Same as State Trigger

		// Complete Effect
		completeEffect = "= {\n";
		completeEffect += "\t\t\tset_cosmetic_tag = " + tag + "\n";
		completeEffect += "\t\t\tevery_state = {\n";
		completeEffect += "\t\t\t\tlimit = {\n";
		completeEffect += "\t\t\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			completeEffect += "\t\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		completeEffect += "\t\t\t\t\t}\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t\tadd_core_of = ROOT\n";
		completeEffect += "\t\t\t\tremove_core_of = " + oldTag + "\n";
		completeEffect += "\t\t\t}\n";
		completeEffect += "\t\t\tevery_state = {\n ";
		completeEffect += "\t\t\t\tlimit = {\n ";
		completeEffect += "\t\t\t\t\tis_claimed_by = " + oldTag + "\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t\tadd_claim_by = ROOT\n";
		completeEffect += "\t\t\t\tremove_claim_by = " + oldTag + "\n";
		completeEffect += "\t\t\t}\n";
		completeEffect += "\t\t\tevery_possible_country = {\n ";
		completeEffect += "\t\t\t\tlimit = {\n ";
		completeEffect += "\t\t\t\t\tNOT = { tag = ROOT }\n";
		completeEffect += "\t\t\t\t\thas_cosmetic_tag = " + tag + "\n";
		completeEffect += "\t\t\t\t}\n";
		completeEffect += "\t\t\t\tdrop_cosmetic_tag = yes\n";
		completeEffect += "\t\t\t}\n";
		completeEffect += "\t\t}";
		formationDecision.setCompleteEffect(completeEffect);

		// AI Will Do
		formationDecision.setAiWillDo("= {\n\t\t\tbase = 100\n\t\t}");

		// Add to Category
		formable_decisions_category.addDecision(formationDecision);
	}

	decisions.push_back(formable_decisions_category);
}