#include "AgentRecruitmentDecisions.h"



void HoI4::AgentRecruitmentDecisions::updateDecisions()
{
	for (auto category: decisions)
	{
		std::smatch match;
		auto categoryDecisions = category.getDecisions();
		categoryDecisions.erase(std::remove_if(categoryDecisions.begin(),
											 categoryDecisions.end(),
											 [&match](auto& decision) {
												 auto name = decision.getName();
												 return std::regex_search(name, match, std::regex("india"));
											 }),
			 categoryDecisions.end());
		category.replaceDecisions(categoryDecisions);

		for (auto decision: category.getDecisions())
		{
			if (decision.getName() == "recruit_in_asia_state")
			{
				decision.setTargetTrigger(
					 "= {\n"
					 "\t\t\tFROM = {\n"
					 "\t\t\t\tis_on_continent = asia\n"
					 "\t\t\t\tCONTROLLER = {\n"
					 "\t\t\t\t\tNOT = {\n"
					 "\t\t\t\t\t\ttag = ROOT\n"
					 "\t\t\t\t\t}\n"
					 "\t\t\t\t}\n"
					 "\t\t\t\tis_capital = yes\n"
					 "\t\t\t}\n"
					 "\t\t}");
				decision.setVisible(
					 "= {\n"
					 "\t\t\tOR = {\n"
					 "\t\t\t\thas_country_flag = asia_recruitment_unlocked\n"
					 "\t\t\t\tcapital_scope = { is_on_continent = asia }\n"
					 "\t\t\t}\n"
					 "\t\t\tNOT = { has_country_flag = asia_recruitment_in_process }\n"
					 "\t\t}");

				category.replaceDecision(decision);
			}
		}
		std::replace(decisions.begin(), decisions.end(), category, category);
	}
}