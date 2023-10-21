#include "src/HOI4World/Decisions/AgentRecruitmentDecisions.h"
#include <sstream>



void HoI4::AgentRecruitmentDecisions::updateDecisions(const std::set<std::string>& southAsianCountries)
{
	for (auto category: decisions)
	{
		for (auto decision: category.getDecisions())
		{
			if (decision.getName() == "recruit_in_india")
			{
				std::stringstream visible;
				visible << "= {\n";
				visible << "\t\t\tNOT = {\n";
				visible << "\t\t\t\thas_country_flag = conv_south_asia\n";
				visible << "\t\t\t}\n";
				visible << "\t\t\tOR = {\n";
				if (!southAsianCountries.empty())
				{
					visible << "\t\t\t\tany_owned_state = {\n";
					visible << "\t\t\t\t\tOR = {\n";
					for (const auto& southAsianCountry: southAsianCountries)
					{
						visible << "\t\t\t\t\t\tis_core_of = " << southAsianCountry << "\n";
					}
					visible << "\t\t\t\t\t}\n";
					visible << "\t\t\t\t}\n";
					for (const auto& southAsianCountry: southAsianCountries)
					{
						visible << "\t\t\t\tis_in_faction_with = " << southAsianCountry << "\n";
					}
				}
				visible << "\t\t\t\tany_of_scopes = {\n";
				visible << "\t\t\t\t\tarray = subjects\n";
				visible << "\t\t\t\t\thas_country_flag = conv_south_asia\n";
				visible << "\t\t\t\t}\n";
				visible << "\t\t\t}\n";
				visible << "\t\t}";
				decision.setVisible(visible.str());

				category.replaceDecision(decision);
			}
			if (decision.getName() == "recruit_in_india_state")
			{
				decision.setTargetRootTrigger(
					"= {\n"
					"\t\t\tOR = {\n"
					"\t\t\t\thas_country_flag = india_recruitment_unlocked\n"
					"\t\t\t\thas_country_flag = conv_south_asia\n"
					"\t\t\t}\n"
					"\t\t\tNOT = { has_country_flag = india_recruitment_in_process }\n"
					"\t\t}\n");
				decision.setTargetTrigger(
					 "= {\n"
					 "\t\t\tFROM = {\n"
					 "\t\t\t\tOR = {\n"
					 "\t\t\t\t\tAND = {\n"
					 "\t\t\t\t\t\thas_variable = historical_capital_for_country\n"
					 "\t\t\t\t\t\tvar:historical_capital_for_country = {\n"
					 "\t\t\t\t\t\t\tOR = {\n"
					 "\t\t\t\t\t\t\t\thas_capitulated = yes\n"
					 "\t\t\t\t\t\t\t\texists = no\n"
					 "\t\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t\t\tNOT = { tag = ROOT }\n"
					 "\t\t\t\t\t\t\thas_country_flag = conv_south_asia\n"
					 "\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t}\n"
					 "\t\t\t\t\tAND = {\n"
					 "\t\t\t\t\t\tis_capital = yes\n"
					 "\t\t\t\t\t\tCONTROLLER = {\n"
					 "\t\t\t\t\t\t\tNOT = {\n"
					 "\t\t\t\t\t\t\t\ttag = ROOT\n"
					 "\t\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t\t\thas_country_flag = conv_south_asia\n"
					 "\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t}\n"
					 "\t\t\t\t}\n"
					 "\t\t\t}\n"
					 "\t\t}");
				decision.setVisible(
					 "= {\n"
					 "\t\t\tOR = {\n"
					 "\t\t\t\thas_country_flag = india_recruitment_unlocked\n"
					 "\t\t\t\thas_country_flag = conv_south_asia\n"
					 "\t\t\t}\n"
					 "\t\t\tNOT = { has_country_flag = india_recruitment_in_process }\n"
					 "\t\t}");

				category.replaceDecision(decision);
			}
			if (decision.getName() == "recruit_in_asia_state")
			{
				decision.setTargetRootTrigger(
					"= {\n"
					"\t\t\tOR = {\n"
					"\t\t\t\thas_country_flag = asia_recruitment_unlocked\n"
					"\t\t\t\tcapital_scope = {\n"
					"\t\t\t\t\tis_on_continent = asia\n"
					"\t\t\t\t}\n"
					"\t\t\t}\n"
					"\t\t\tNOT = { has_country_flag = conv_south_asia }\n"
					"\t\t\tNOT = { has_country_flag = asia_recruitment_in_process }\n"
					"\t\t}\n");
				decision.setTargetTrigger(
					 "= {\n"
					 "\t\t\tFROM = {\n"
					 "\t\t\t\tOR = {\n"
					 "\t\t\t\t\tAND = {\n"
					 "\t\t\t\t\t\thas_variable = historical_capital_for_country\n"
					 "\t\t\t\t\t\tvar:historical_capital_for_country = {\n"
					 "\t\t\t\t\t\t\tOR = {\n"
					 "\t\t\t\t\t\t\t\thas_capitulated = yes\n"
					 "\t\t\t\t\t\t\t\texists = no\n"
					 "\t\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t\t\tNOT = { tag = ROOT }\n"
					 "\t\t\t\t\t\t\tNOT = { has_country_flag = conv_south_asia }\n"
					 "\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t}\n"
					 "\t\t\t\t\tAND = {\n"
					 "\t\t\t\t\t\tis_capital = yes\n"
					 "\t\t\t\t\t\tCONTROLLER = {\n"
					 "\t\t\t\t\t\t\tNOT = {\n"
					 "\t\t\t\t\t\t\t\ttag = ROOT\n"
					 "\t\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t\t\tNOT = { has_country_flag = conv_south_asia }\n"
					 "\t\t\t\t\t\t}\n"
					 "\t\t\t\t\t}\n"
					 "\t\t\t\t}\n"
					 "\t\t\t}\n"
					 "\t\t}");
				decision.setVisible(
					 "= {\n"
					 "\t\t\tOR = {\n"
					 "\t\t\t\thas_country_flag = asia_recruitment_unlocked\n"
					 "\t\t\t\tcapital_scope = {\n"
					 "\t\t\t\t\tis_on_continent = asia\n"
					 "\t\t\t\t}\n"
					 "\t\t\t}\n"
					 "\t\t\tNOT = {\n"
					 "\t\t\t\thas_country_flag = conv_south_asia\n"
					 "\t\t\t}\n"
					 "\t\t\tNOT = { has_country_flag = asia_recruitment_in_process }\n"
					 "\t\t}");

				category.replaceDecision(decision);
			}
		}
		std::replace(decisions.begin(), decisions.end(), category, category);
	}
}