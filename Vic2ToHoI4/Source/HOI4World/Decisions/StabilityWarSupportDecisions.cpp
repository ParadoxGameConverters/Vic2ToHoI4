#include "StabilityWarSupportDecisions.h"



std::pair<std::string, std::string> determineIdeologiesForStabilityDecisions(
	 const std::set<std::string>& majorIdeologies);
bool stabilityDecisionToUpdate(const std::string& decisionName);
std::string updateTimeoutEffect(std::string& originalEffect,
	 const std::pair<std::string, std::string>& ideologiesForStabilityDecisions);


void HoI4::StabilityWarSupportDecisions::updateDecisions(const std::set<std::string>& majorIdeologies)
{
	const auto ideologiesForStabilityDecisions = determineIdeologiesForStabilityDecisions(majorIdeologies);

	for (auto category: decisions)
	{
		auto updated = false;
		for (auto decision: category.getDecisions())
		{
			if (stabilityDecisionToUpdate(decision.getName()))
			{
				auto timeoutEffect = decision.getTimeoutEffect();
				timeoutEffect = updateTimeoutEffect(timeoutEffect, ideologiesForStabilityDecisions);
				decision.setTimeoutEffect(timeoutEffect);
				category.replaceDecision(decision);
				updated = true;
			}
			if (decision.getName() == "demobilization_manpower")
			{
				decision.setVisible(
					 "= {\n"
					 "\t\t\thas_unsupported_manpower_law = yes\n"
					 "\t\t\thas_war = no\n"
					 "\t\t}");
				category.replaceDecision(decision);
				updated = true;
			}
			if (decision.getName() == "demob_manpower_mission")
			{
				decision.setActivation(
					 "= {\n"
					 "\t\t\thas_unsupported_manpower_law = yes\n"
					 "\t\t\thas_war = no\n"
					 "\t\t}");
				decision.setVisible("");
				category.replaceDecision(decision);
				updated = true;
			}
		}
		if (updated)
		{
			std::replace(decisions.begin(), decisions.end(), category, category);
		}
	}
}


std::pair<std::string, std::string> determineIdeologiesForStabilityDecisions(
	 const std::set<std::string>& majorIdeologies)
{
	std::pair<std::string, std::string> theIdeologies;

	if (majorIdeologies.contains("communism"))
	{
		theIdeologies.first = "communism";
	}
	else if (majorIdeologies.contains("absolutist"))
	{
		theIdeologies.first = "absolutist";
	}
	else
	{
		theIdeologies.first = "neutrality";
	}

	if (majorIdeologies.contains("democratic"))
	{
		theIdeologies.second = "democratic";
	}
	else if (majorIdeologies.contains("radical"))
	{
		theIdeologies.second = "radical";
	}
	else
	{
		theIdeologies.second = "neutrality";
	}

	return theIdeologies;
}


bool stabilityDecisionToUpdate(const std::string& decisionName)
{
	return decisionName == "draft_dodging_mission" || decisionName == "strikes_mission" ||
			 decisionName == "mutiny_mission" || decisionName == "demob_economic_mission" ||
			 decisionName == "demob_manpower_mission";
}


std::string updateTimeoutEffect(std::string& originalEffect,
	 const std::pair<std::string, std::string>& ideologiesForStabilityDecisions)
{
	auto index = originalEffect.find("communism");
	while (index != std::string::npos)
	{
		originalEffect.replace(index, 9, ideologiesForStabilityDecisions.first);
		index = originalEffect.find("communism", index + ideologiesForStabilityDecisions.first.length());
	}

	index = originalEffect.find("democratic");
	while (index != std::string::npos)
	{
		originalEffect.replace(index, 10, ideologiesForStabilityDecisions.second);
		index = originalEffect.find("democratic", index + ideologiesForStabilityDecisions.second.length());
	}

	return originalEffect;
}