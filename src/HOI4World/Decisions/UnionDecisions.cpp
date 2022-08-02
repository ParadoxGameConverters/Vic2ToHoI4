#include "src/HOI4World/Decisions/UnionDecisions.h"

void HoI4::UnionDecisions::createDecisions(const std::vector<HoI4::UnionCountry>& unionCountries)
{
	DecisionsInCategory formable_decisions_category("formable_decisions");
	for (auto unionCountry: unionCountries)
	{
		const auto& name = "form_" + unionCountry.GetTag() + "_union";
		decision formationDecision(name);
		const auto& tag = unionCountry.GetTag();

		// Allowed
		std::string allowed = "NOT = { has_original_tag = " + tag + " }\n";
		allowed += "OR = {\n";
		for (const auto& culture: unionCountry.GetCultures())
		{
			allowed += "\thas_idea = culture_" + culture + "\n";
		}
		allowed += "}\n";
		formationDecision.setAllowed(allowed);

		// Visible
		std::string visible = "NOT = {\n";
		visible += "\t" + tag + "= { exists = no }\n";
		visible += "}\n";
		formationDecision.setVisible(visible);

		// Available
		std::string available = "NOT = {\n";
		available += "\tany_other_country = {\n";
		available += "\t\thas_cosmetic_tag =" + tag + "_union\n";
		available += "\t\texists = yes\n";
		available += "\t}\n}\n";
		available += "all_state = {\n";
		available += "\tif = { \n";
		available += "\t\tlimit = { is_core_of = " + tag + "}\n";
		available += "\t\tis_controlled_by = ROOT\n";
		available += "\t}\n}\n";
		formationDecision.setAvailable(available);

		// Complete Effect
		std::string completeEffect = "set_cosmetic_flag = " + tag + "_union\n";
		completeEffect += "every_state = {\n";
		completeEffect += "\tlimit = {\n";
		completeEffect += "\t\tOR = {\n";
		completeEffect += "\t\t\tis_core_of = " + tag;
		completeEffect += "\t\t\tany_country = {\n";
		completeEffect += "\t\t\t\thas_cosmetic_tag = " + tag + "_union\n";
		completeEffect += "\t\t\t\tPREV = { is_core_of = THIS }\n";
		completeEffect += "\t\t\t}\n\t\t}\n\t}\n";
		completeEffect += "\tadd_core_of = ROOT\n";
		completeEffect += "}";
		formationDecision.setCompleteEffect(completeEffect);

		// AI Will Do
		formationDecision.setAiWillDo("base = 100");

		// Add to Category
		formable_decisions_category.addDecision(formationDecision);
	}

	decisions.push_back(formable_decisions_category);
}