#include "src/HOI4World/Decisions/ExiledGovernmentsDecisions.h"
#include <algorithm>
#include <sstream>



HoI4::decision&& updatePurgeInfiltrators(HoI4::decision&& theDecision, const std::set<std::string>& majorIdeologies)
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
	theDecision.setAvailable(available.str());

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
	theDecision.setVisible(visibleAndTT.str());
	theDecision.setTargetTrigger(visibleAndTT.str());

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
	theDecision.setTargetedModifier(targetedModifier.str());

	return std::move(theDecision);
}


HoI4::decision&& updateExileRecruitmentCampaign(HoI4::decision&& theDecision)
{
	std::stringstream targetTrigger;
	targetTrigger << "= {\n";
	targetTrigger << "\t\t\tFROM = { is_hosting_exile = ROOT }\n";
	targetTrigger << "\t\t}";
	theDecision.setTargetTrigger(targetTrigger.str());

	return std::move(theDecision);
}


HoI4::decision&& updateExileExtractionCampaigns(HoI4::decision&& theDecision)
{
	std::stringstream targetTrigger;
	targetTrigger << "= {\n";
	targetTrigger << "\t\t\tFROM = { is_exiled_in = ROOT }\n";
	targetTrigger << "\t\t}";
	theDecision.setTargetTrigger(targetTrigger.str());

	return std::move(theDecision);
}


void HoI4::ExiledGovernmentsDecisions::updateDecisions(const std::set<std::string>& majorIdeologies)
{
	for (auto category: decisions)
	{
		for (auto decision: category.getDecisions())
		{
			if (decision.getName() == "purge_infiltrators")
			{
				category.replaceDecision(updatePurgeInfiltrators(std::move(decision), majorIdeologies));
			}
			else if (decision.getName() == "exile_recruitment_campaign")
			{
				category.replaceDecision(updateExileRecruitmentCampaign(std::move(decision)));
			}
			else if (decision.getName() == "exile_extraction_campaign")
			{
				category.replaceDecision(updateExileExtractionCampaigns(std::move(decision)));
			}
		}

		std::ranges::replace(decisions, category, category);
	}
}