#include "src/HOI4World/Decisions/UnionDecisions.h"

void HoI4::UnionDecisions::createDecisions(const std::vector<HoI4::UnionCountry>& unionCountries)
{
	DecisionsInCategory formableDecisionsCategory("formable_nations");
	for (auto unionCountry: unionCountries)
	{
		const auto& oldTag = unionCountry.GetTag().substr(0, 2);
		const auto& tag = unionCountry.GetTag();
		const auto& name = "form_" + tag;
		decision formationDecisionStateTrigger(name + "_state_trigger");
		decision formationDecision(name);
		DecisionsInCategory::LocBlock locBlock;

		// Custom Loc
		formableDecisionsCategory.addCustomLocalisation(
			 std::pair(name + "_loc_DEF", "\t= {\n\t\tlocalization_key = " + tag + "_DEF\n\t}"));
		formableDecisionsCategory.addCustomLocalisation(
			 std::pair(name + "_loc_ADJ", "\t= {\n\t\tlocalization_key = " + tag + "_ADJ\n\t}"));

		// STATE TRIGGER
		// Allowed
		std::string allowed = "= {\n";
		allowed += "\t\t\tNOT = { original_tag = " + oldTag + " }\n";
		allowed += "\t\t}";
		formationDecisionStateTrigger.setAllowed(allowed);

		// State Target/On Map Mode/Icon
		formationDecisionStateTrigger.setStateTarget(true);
		formationDecisionStateTrigger.setOnMapMode("map_only");
		formationDecisionStateTrigger.setIcon("decision_generic_nationalism");

		// Target ROOT Trigger
		std::string targetRootTrigger = "= {\n";
		targetRootTrigger += "\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			targetRootTrigger += "\t\t\t\thas_idea = culture_" + culture + "\n";
		}
		targetRootTrigger += "\t\t\t}\n";
		targetRootTrigger += "\t\t\tNOT = { has_cosmetic_tag = " + tag + " }\n";
		targetRootTrigger += "\t\t\t" + oldTag + " = { exists = no }\n";
		targetRootTrigger += "\t\t}\n";
		formationDecisionStateTrigger.setTargetRootTrigger(targetRootTrigger);

		// Target Trigger
		std::string targetTrigger = "= {\n";
		targetTrigger += "\t\t\tFROM = {\n";
		targetTrigger += "\t\t\t\tOR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			targetTrigger += "\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		targetTrigger += "\t\t\t\t}\n";
		targetTrigger += "\t\t\t}\n";
		targetTrigger += "\t\t}\n";
		formationDecisionStateTrigger.setTargetTrigger(targetTrigger);

		// Highlight States
		std::string highlightStates = "= {\n";
		highlightStates += "\t\t\thighlight_states_trigger = {\n";
		highlightStates += "\t\t\t\t OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			highlightStates += "\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		highlightStates += "\t\t\t\t}\n";
		highlightStates += "\t\t\t}\n";
		highlightStates += "\t\t\thighlight_color_before_active = 1\n";
		highlightStates += "\t\t\thighlight_color_while_active = 2\n";
		highlightStates += "\t\t}";
		formationDecisionStateTrigger.setHighlightStateTargets(highlightStates);

		// Available
		std::string available = "= {\n";
		available += "\t\t\thidden_trigger = {\n";
		available += "\t\t\t\tset_temp_variable = { temp_original_states = 0 }\n";
		available += "\t\t\t\tset_temp_variable = { original_states = 0 }\n";
		available += "\t\t\t\tif = {\n";
		available += "\t\t\t\t\tlimit = {\n";
		available += "\t\t\t\t\t\tall_state = {\n";
		available += "\t\t\t\t\t\t\tif = {\n";
		available += "\t\t\t\t\t\t\t\tlimit = {\n";
		available += "\t\t\t\t\t\t\t\t\tOR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			available += "\t\t\t\t\t\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		available += "\t\t\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t\t\tadd_to_temp_variable = { ROOT.original_states = 1 }\n";
		available += "\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t}\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t\tif = {\n";
		available += "\t\t\t\t\tlimit = {\n";
		available += "\t\t\t\t\t\tall_controlled_state = {\n";
		available += "\t\t\t\t\t\t\tif = {\n";
		available += "\t\t\t\t\t\t\t\tlimit = {\n";
		available += "\t\t\t\t\t\t\t\t\tOR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			available += "\t\t\t\t\t\t\t\t\t\thas_state_flag = major_culture_" + culture + "_flag\n";
		}
		available += "\t\t\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t\t\tadd_to_temp_variable = { ROOT.temp_original_states = 1 }\n";
		available += "\t\t\t\t\t\t\t}\n";
		available += "\t\t\t\t\t\t}\n";
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
		available += "\t\t\t\t\thas_cosmetic_tag = " + tag + "\n";
		available += "\t\t\t\t\texists = yes\n";
		available += "\t\t\t\t}\n";
		available += "\t\t\t}\n";
		available += "\t\t}";
		formationDecisionStateTrigger.setAvailable(available);

		// Complete Effect
		std::string completeEffect = "= {\n";
		completeEffect += "\t\t\tactivate_decision = " + name + "\n";
		completeEffect += "\t\t}";
		formationDecisionStateTrigger.setCompleteEffect(completeEffect);

		// AI Will Do
		formationDecisionStateTrigger.setAiWillDo("= {\n\t\t\tbase = 100\n\t\t}");

		// Localisation
		locBlock.english = "[" + name + "_loc_ADJ] State";
		locBlock.french =  "One of the [?original_states] states needed to form [" + name + "_loc_DEF].";
		locBlock.german = "[" + name + "_loc_ADJ] Zustand";
		locBlock.polish = "[" + name + "_loc_ADJ] państwo";
		locBlock.portuguese = "[" + name + "_loc_ADJ] Estado";
		locBlock.russian = "[" + name + "_loc_ADJ] государство";
		locBlock.spanish = "[" + name + "_loc_ADJ] Estado";
		formableDecisionsCategory.addLocalisation(std::pair(name + "_state_trigger", locBlock));
		locBlock.english = "One of the [?original_states] states needed to form [" + name + "_loc_DEF].";
		locBlock.french = "L'un des états [?original_states] nécessaires pour former [" + name + "_loc_DEF].";
		locBlock.german = "Einer der [?original_states]-Zustände, die zum Bilden von [" + name + "_loc_DEF] benötigt werden.";
		locBlock.polish = "Jeden ze stanów [?original_states] potrzebnych do utworzenia [" + name + "_loc_DEF].";
		locBlock.portuguese = "Um dos estados [?original_states] precisava formar [" + name + "_loc_DEF].";
		locBlock.russian = "Одно из состояний [?original_states], необходимое для формирования [" + name + "_loc_DEF].";
		locBlock.spanish = "Uno de los estados [?original_states] necesarios para formar [" + name + "_loc_DEF].";
		formableDecisionsCategory.addLocalisation(std::pair(name + "_state_trigger_desc", locBlock));

		// Add to Category
		formableDecisionsCategory.addDecision(formationDecisionStateTrigger);


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
		visible += "\t\t\tNOT = { has_cosmetic_tag = " + tag + " }\n";
		visible += "\t\t\t" + oldTag + " = { exists = no }\n";
		visible += "\t\t}";
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

		// Localisation
		locBlock.english = "Form [" + name + "_loc_DEF]";
		locBlock.french = "Formulaire [" + name + "_loc_DEF]";
		locBlock.german = "Formular [" + name + "_loc_DEF]";
		locBlock.polish = "Formularz [" + name + "_loc_DEF]";
		locBlock.portuguese = "Formar [" + name + "_loc_DEF]";
		locBlock.russian = "Форма [" + name + "_loc_DEF]";
		locBlock.spanish = "Formulario [" + name + "_loc_DEF]";
		formableDecisionsCategory.addLocalisation(std::pair(name, locBlock));
		locBlock.english =  "Our great people have been separated for too long, kept apart by foreign powers who would keep us divided and weak. Now we stand united against any who would dare try to separate us again.";
		locBlock.french = "Notre grand peuple a été séparé pendant trop longtemps, tenu à l'écart par des puissances étrangères qui nous garderaient divisés et faibles. Maintenant, nous sommes unis contre quiconque oserait essayer de nous séparer à nouveau.";
		locBlock.german = "Unser großartiges Volk war zu lange getrennt, getrennt gehalten von fremden Mächten, die uns gespalten und schwach halten würden. Jetzt stehen wir vereint gegen jeden, der es wagen würde, uns wieder zu trennen.";
		locBlock.polish = "Nasi wielcy ludzie byli rozdzieleni zbyt długo, trzymani osobno przez obce mocarstwa, które trzymałyby nas podzielonych i słabych. Teraz stajemy zjednoczeni przeciwko każdemu, kto ośmieliłby się ponownie nas rozdzielić.";
		locBlock.portuguese = "Nosso grande povo foi separado por muito tempo, mantido à parte por potências estrangeiras que nos manteriam divididos e fracos. Agora estamos unidos contra qualquer um que ousaria tentar nos separar novamente.";
		locBlock.russian = "Наш великий народ слишком долго был разлучен, его держали в стороне иностранные державы, которые хотели, чтобы мы были разделены и слабы. Теперь мы объединились против любого, кто посмеет снова попытаться разлучить нас.";
		locBlock.spanish = "Nuestro gran pueblo ha estado separado durante demasiado tiempo, mantenido aparte por potencias extranjeras que nos mantendrían divididos y débiles. Ahora estamos unidos contra cualquiera que se atreva a intentar separarnos de nuevo.";
		formableDecisionsCategory.addLocalisation(std::pair(name + "_desc", locBlock));

		// Add to Category
		formableDecisionsCategory.addDecision(formationDecision);
	}

	decisions.push_back(formableDecisionsCategory);
}