#include "src/HOI4World/Decisions/UnionDecisions.h"

void HoI4::UnionDecisions::createDecisions(const std::vector<HoI4::UnionCountry>& unionCountries)
{
	DecisionsInCategory formable_decisions_category("formable_nations");
	for (auto unionCountry: unionCountries)
	{
		const auto& oldTag = unionCountry.GetOldTag();
		const auto& tag = unionCountry.GetTag();
		const auto& name = "form_" + tag;
		decision formationDecision(name);

		// Fire Only Once
		//formationDecision.setFireOnlyOnce(true);

		// Allowed
		std::string allowed = "= {\n";
		allowed += "\t\t\tNOT = { original_tag = " + oldTag + " }\n";
		allowed += "\t\t}\n";
		formationDecision.setAllowed(allowed);

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
		std::string available = "= {\n";
		available += "\t\t\tNOT = {\n";
		available += "\t\t\t\tany_other_country = {\n";
		available += "\t\t\t\t\thas_cosmetic_tag = " + tag + "\n";
		available += "\t\t\t\t\texists = yes\n";
		available += "\t\t\t\t}\n\t\t\t}\n";
		available += "\t\t\tall_state = {\n";
		available += "\t\t\t\tif = { \n";
		available += "\t\t\t\t\tlimit = { is_core_of = " + oldTag + " }\n";
		available += "\t\t\t\t\tis_controlled_by = ROOT\n";
		available += "\t\t\t\t}\n\t\t\t}\n\t\t}\n";
		formationDecision.setAvailable(available);

		// Complete Effect
		std::string completeEffect = "= {\n";
		completeEffect += "\t\t\tset_cosmetic_tag = " + tag + "\n";
		completeEffect += "\t\t\tevery_state = {\n";
		completeEffect += "\t\t\t\tlimit = {\n";
		completeEffect += "\t\t\t\t\tOR = {\n";
		completeEffect += "\t\t\t\t\t\tis_core_of = " + oldTag + "\n";
		completeEffect += "\t\t\t\t\t\tany_country = {\n";
		completeEffect += "\t\t\t\t\t\t\thas_cosmetic_tag = " + tag + "\n";
		completeEffect += "\t\t\t\t\t\t\tPREV = { is_core_of = THIS }\n";
		completeEffect += "\t\t\t\t\t\t}\n\t\t\t\t\t}\n\t\t\t\t}\n";
		completeEffect += "\t\t\t\tadd_core_of = ROOT\n";
		completeEffect += "\t\t\t}\n\t\t}";
		formationDecision.setCompleteEffect(completeEffect);

		// AI Will Do
		formationDecision.setAiWillDo("= {\n\t\t\tbase = 100\n\t\t}");

		// Add to Category
		formable_decisions_category.addDecision(formationDecision);
	}

	decisions.push_back(formable_decisions_category);
}