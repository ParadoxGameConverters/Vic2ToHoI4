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