#include "ForeignInfluenceDecisions.h"



std::regex createIdeologyRegex(const std::set<std::string>& majorIdeologies);


void HoI4::ForeignInfluenceDecisions::updateDecisions(const std::set<std::string>& majorIdeologies)
{
	const auto ideologyRegex = createIdeologyRegex(majorIdeologies);
	for (auto& category: decisions)
	{
		std::smatch ideologyMatch;
		auto decisions = category.getDecisions();
		decisions.erase(std::remove_if(decisions.begin(),
								  decisions.end(),
								  [&ideologyMatch, &ideologyRegex](auto& decision) {
									  if (decision.getName() == "instantiate_collaboration")
									  {
										  return false;
									  }
									  auto visible = decision.getVisible();
									  return !std::regex_search(visible, ideologyMatch, ideologyRegex);
								  }),
			 decisions.end());
		category.replaceDecisions(decisions);

		for (auto decision: category.getDecisions())
		{
			if (decision.getName() == "instantiate_collaboration")
			{
				std::string aiWillDo;
				aiWillDo += "= {\n";
				aiWillDo += "\t\t\tbase = 10\n";
				aiWillDo += "\t\t\t# priotize larger countries\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\tmodifier = {\n";
				aiWillDo += "\t\t\t\t# neutrals won't do collaboration until 1944 and they are at peace\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\thas_government = neutrality\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\tOR = {\n";
				aiWillDo += "\t\t\t\t\thas_war = yes\n";
				aiWillDo += "\t\t\t\t\tdate < 1944.01.01\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\tfactor = 0\n";
				aiWillDo += "\t\t\t}\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\tmodifier = {\n";
				aiWillDo += "\t\t\t\t# calculating cores we control\n";
				aiWillDo += "\t\t\t\tset_temp_variable = { num_cores_we_control = 0 }\n";
				aiWillDo += "\t\t\t\tall_of_scopes = {\n";
				aiWillDo += "\t\t\t\t\tarray = FROM.core_states\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\t\tif = {\n";
				aiWillDo += "\t\t\t\t\t\tlimit = { is_controlled_by = PREV }\n";
				aiWillDo += "\t\t\t\t\t\tadd_to_temp_variable = { num_cores_we_control = 1 }\n";
				aiWillDo += "\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\t# more score if more cores are controlled by us\n";
				aiWillDo += "\t\t\t\tadd = num_cores_we_control\n";
				aiWillDo += "\t\t\t}\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t# dont make too many collaboratios\n";
				aiWillDo += "\t\t\tmodifier = {\n";
				aiWillDo += "\t\t\t\t# as number of collaboration subjects increases\n";
				aiWillDo += "\t\t\t\t# only accept subjects with more cores\n";
				aiWillDo += "\t\t\t\tset_temp_variable = { num_min_cores = 1.5 }\n";
				aiWillDo += "\t\t\t\tall_of_scopes = {\n";
				aiWillDo += "\t\t\t\t\tarray = subjects\n";
				aiWillDo += "\t\t\t\t\tif = {\n";
				aiWillDo += "\t\t\t\t\t\tlimit = {\n";
				aiWillDo += "\t\t\t\t\t\t\thas_autonomy_state = autonomy_collaboration_government\n";
				aiWillDo += "\t\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t\t\tadd_to_temp_variable = { num_min_cores = 0.7 }\n";
				aiWillDo += "\t\t\t\t\t}\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\tcheck_variable = { num_cores_we_control < num_min_cores }\n";
				aiWillDo += "\n";
				aiWillDo += "\t\t\t\tfactor = 0\n";
				aiWillDo += "\t\t\t}\n";
				aiWillDo += "\t\t}\n";
				aiWillDo += "\t\t# don't create collab governments if you have contested cores\n";
				aiWillDo += "\t\tmodifier = {\n";
				aiWillDo += "\t\t\tany_state = {\n";
				aiWillDo += "\t\t\t\tOR = {\n";
				aiWillDo += "\t\t\t\t\tis_controlled_by = ROOT\n";
				aiWillDo += "\t\t\t\t\tis_owned_by = ROOT\n";
				aiWillDo += "\t\t\t\t}\n";
				aiWillDo += "\t\t\t\tis_core_of = FROM\n";
				aiWillDo += "\t\t\t\tis_core_of = ROOT\n";
				aiWillDo += "\t\t\t}\n";
				aiWillDo += "\t\t\tfactor = 0\n";
				aiWillDo += "\t\t}";
				decision.setAiWillDo(aiWillDo);
				category.replaceDecision(decision);

				continue;
			}

			auto visible = decision.getVisible();
			std::regex_search(visible, ideologyMatch, ideologyRegex);

			std::string newVisible;
			std::smatch typeMatch;
			if (std::regex_search(visible, typeMatch, std::regex("99")))
			{
				newVisible += "= {\n";
				newVisible += "\t\t\thas_government = " + ideologyMatch.str() + "\n";
				newVisible += "\t\t\tFROM = {\n";
				newVisible += "\t\t\t\tis_puppet_of = ROOT\n";
				newVisible += "\t\t\t\t" + ideologyMatch.str() + " < 0.99\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
			}
			else
			{
				newVisible += "= {\n";
				newVisible += "\t\t\thas_government = " + ideologyMatch.str() + "\n";
				newVisible += "\t\t\tFROM = {\n";
				newVisible += "\t\t\t\tis_puppet_of = ROOT\n";
				newVisible += "\t\t\t\tNOT = { has_government = " + ideologyMatch.str() + " }\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
			}
			decision.setVisible(newVisible);

			category.replaceDecision(decision);
		}
	}
}


std::regex createIdeologyRegex(const std::set<std::string>& majorIdeologies)
{
	std::string regexString{"("};
	for (const auto& ideology: majorIdeologies)
	{
		regexString += ideology + "|";
	}
	regexString.pop_back();
	regexString += ")";
	return std::regex{regexString};
}