#include "DecisionsCategoriesOutputter.h"



void HoI4::outputDecisionCategories(std::ostream& out, const std::set<std::string>& majorIdeologies)
{
	if (majorIdeologies.count("fascism") > 0)
	{
		out << "fascism_on_the_rise = {\n";
		out << "\ticon = generic_fascism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = fascism }\n";
		out << "\t#	has_idea_with_trait = fascism_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (majorIdeologies.count("absolutist") > 0)
	{
		out << "absolutist_on_the_rise = {\n";
		out << "\ticon = generic_fascism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = absolutist }\n";
		out << "\t#	has_idea_with_trait = absolutist_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (majorIdeologies.count("democratic") > 0)
	{
		out << "democratic_on_the_rise = {\n";
		out << "\ticon = generic_democracy\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = democratic }\n";
		out << "\t#	has_idea_with_trait = democratic_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (majorIdeologies.count("communism") > 0)
	{
		out << "communism_on_the_rise = {\n";
		out << "\ticon = generic_communism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = communism }\n";
		out << "\t#	has_idea_with_trait = communism_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
	if (majorIdeologies.count("radical") > 0)
	{
		out << "radical_on_the_rise = {\n";
		out << "\ticon = generic_communism\n";
		out << "\n";
		out << "\tallowed = {\n";
		out << "\t\talways = yes\n";
		out << "\t}\n";
		out << "\n";
		out << "\t#visible = {\n";
		out << "\t#	NOT = { has_government = radical }\n";
		out << "\t#	has_idea_with_trait = radical_minister\n";
		out << "\t#}\n";
		out << "}\n";
		out << "\n";
	}
}