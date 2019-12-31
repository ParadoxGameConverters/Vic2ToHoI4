#include "StabilityWarSupportDecisions.h"



HoI4::StabilityWarSupportDecisions::StabilityWarSupportDecisions(std::istream& theStream)
{
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		decisions.push_back(category);
	});

	parseStream(theStream);
}


std::pair<std::string, std::string> determineIdeologiesForStabilityDecisions(
	const std::set<std::string>& majorIdeologies
);
bool stabilityDecisionToUpdate(const std::string& decisionName);
std::string updateTimeoutEffect(
	std::string& originalEffect,
	const std::pair<std::string, std::string>& ideologiesForStabilityDecisions
);


void HoI4::StabilityWarSupportDecisions::updateDecisions(const std::set<std::string>& majorIdeologies)
{
	const auto ideologiesForStabilityDecisions = determineIdeologiesForStabilityDecisions(majorIdeologies);

	for (auto category: decisions)
	{
		auto updated = false;
		for (auto decision : category.getDecisions())
		{
			if (stabilityDecisionToUpdate(decision.getName()))
			{
				auto timeoutEffect = decision.getTimeoutEffect();
				timeoutEffect = updateTimeoutEffect(timeoutEffect, ideologiesForStabilityDecisions);
				decision.setTimeoutEffect(timeoutEffect);
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
	const std::set<std::string>& majorIdeologies
)
{
	std::pair<std::string, std::string> theIdeologies;

	if (majorIdeologies.count("communism") > 0)
	{
		theIdeologies.first = "communism";
	}
	else if (majorIdeologies.count("absolutist") > 0)
	{
		theIdeologies.first = "absolutist";
	}
	else
	{
		theIdeologies.first = "neutrality";
	}

	if (majorIdeologies.count("democratic") > 0)
	{
		theIdeologies.second = "democratic";
	}
	else if (majorIdeologies.count("radical") > 0)
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
	return
		decisionName == "draft_dodging_mission" ||
		decisionName == "strikes_mission" ||
		decisionName == "mutiny_mission" ||
		decisionName == "demob_economic_mission" ||
		decisionName == "demob_manpower_mission";
}


std::string updateTimeoutEffect(
	std::string& originalEffect,
	const std::pair<std::string, std::string>& ideologiesForStabilityDecisions
)
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