#include "ExiledGovernmentsDecisions.h"
#include <sstream>



bool exiledGovernmentDecisionToUpdate(const std::string& decisionName);


void HoI4::ExiledGovernmentsDecisions::updateDecisions(const std::set<std::string>& majorIdeologies)
{
	for (auto category: decisions)
	{
		auto updated = false;
		for (auto decision: category.getDecisions())
		{
			if (exiledGovernmentDecisionToUpdate(decision.getName()))
			{
				std::stringstream available;
				available << "= {\n";
				available << "\t\t\tFROM = {\n";
				available << "\t\t\t\thas_legitimacy > 50\n";
				available << "\t\t\t\tOR = {\n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					available << "\t\t\t\t\t" << ideology << " > 0.1\n";
				}
				available << "\t\t\t\t}\n";
				available << "\t\t\t}\n";
				available << "\t\t}";
				decision.setAvailable(available.str());

				std::stringstream visibleAndTT;
				visibleAndTT << "= {\n";
				visibleAndTT << "\t\t\tFROM = {\n";
				visibleAndTT << "\t\t\t\tis_exiled_in = ROOT\n";
				visibleAndTT << "\t\t\t\thas_legitimacy > 40\n";
				visibleAndTT << "\t\t\t\tOR = {\n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					visibleAndTT << "\t\t\t\t\t" << ideology << " > 0.05\n";
				}
				visibleAndTT << "\t\t\t\t}\n";
				visibleAndTT << "\t\t\t}\n";
				visibleAndTT << "\t\t}";
				decision.setVisible(visibleAndTT.str());
				decision.setTargetTrigger(visibleAndTT.str());

				std::stringstream targetedModifier;
				targetedModifier << "= {\n";
				targetedModifier << "\t\t\ttag = FROM\n";
				targetedModifier << "\t\t\ttargeted_legitimacy_daily = -1\n";
				if (majorIdeologies.contains("democratic"))
				{
					targetedModifier << "\t\t\tdemocratic_drift = 0.05\n";
				}
				else
				{
					targetedModifier << "\t\t\tneutrality_drift = 0.05\n";
				}
				targetedModifier << "\t\t}";
				decision.setTargetedModifier(targetedModifier.str());

				category.replaceDecision(decision);
				updated = true;
				break;
			}
		}
		if (updated)
		{
			std::replace(decisions.begin(), decisions.end(), category, category);
		}
	}
}


bool exiledGovernmentDecisionToUpdate(const std::string& decisionName)
{
	return (decisionName == "purge_infiltrators");
}