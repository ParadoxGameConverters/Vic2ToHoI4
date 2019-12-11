#include "Decisions.h"
#include "Decision.h"
#include "../Events.h"
#include <sstream>



HoI4::decisions::decisions(const Configuration& theConfiguration) noexcept
{
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		stabilityDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/stability_war_support.txt");

	clearRegisteredKeywords();

	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& unused, std::istream& theStream)
	{
		const IdeologicalDecisions ideologicalDecisions(theStream);
		allIdeologicalDecisions.push_back(ideologicalDecisions);
	});
	parseFile("ideologicalDecisions.txt");

	clearRegisteredKeywords();

	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		exiledGovernmentsDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/_exiled_governments_decisions.txt");
}


void HoI4::decisions::updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents)
{
	updateStabilityDecisions(majorIdeologies);
	updatePoliticalDecisions(majorIdeologies, theEvents);
	updateExiledGovernmentDecisions(majorIdeologies);

	decisionsCategories = std::make_unique<DecisionsCategories>(majorIdeologies);
}


bool stabilityDecisionToUpdate(const std::string& decisionName);
std::pair<std::string, std::string> determineIdeologiesForStabilityDecisions(
	const std::set<std::string>& majorIdeologies
);
std::string updateTimeoutEffect(
	std::string& originalEffect,
	const std::pair<std::string, std::string>& ideologiesForStabilityDecisions
);


void HoI4::decisions::updateStabilityDecisions(const std::set<std::string>& majorIdeologies)
{
	const auto ideologiesForStabilityDecisions = determineIdeologiesForStabilityDecisions(majorIdeologies);

	for (auto category: stabilityDecisions)
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
		}
		if (updated)
		{
			std::replace(stabilityDecisions.begin(), stabilityDecisions.end(), category, category);
		}
	}
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


std::string updateTimeoutEffect(
	std::string& originalEffect,
	const std::pair<std::string, std::string>& ideologiesForStabilityDecisions
) {
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


void HoI4::decisions::updatePoliticalDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents)
{
	for (auto ideologicalDecisions: allIdeologicalDecisions)
	{
		if (ideologicalDecisions.requiredIdeologiesExist(majorIdeologies))
		{
			for (const auto& category: ideologicalDecisions.getCategories())
			{
				auto existingCategory = std::find(politicalDecisions.begin(), politicalDecisions.end(), category);
				if (existingCategory == politicalDecisions.end())
				{
					politicalDecisions.push_back(category);
				}
				else
				{
					auto theDecisions = category.getDecisions();
					for (auto& theDecision: theDecisions)
					{
						existingCategory->addDecision(theDecision);
					}
				}
			}
		}
	}

	for (auto& decisionsByIdeology: politicalDecisions)
	{
		decisionsByIdeology.updatePoliticalDecisions(majorIdeologies, theEvents);
	}
}


bool exiledGovernmentDecisionToUpdate(const std::string& decisionName);


void HoI4::decisions::updateExiledGovernmentDecisions(const std::set<std::string>& majorIdeologies)
{
	for (auto category: exiledGovernmentsDecisions)
	{
		auto updated = false;
		for (auto decision: category.getDecisions())
		{
			if (exiledGovernmentDecisionToUpdate(decision.getName()))
			{
				std::stringstream available;
				available << "{\n";
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
				visibleAndTT << "{\n";
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
				targetedModifier << "{\n";
				targetedModifier << "\t\t\ttag = FROM\n";
				targetedModifier << "\t\t\ttargeted_legitimacy_daily = -1\n";
				if (majorIdeologies.count("democratic") > 0)
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
			std::replace(
				exiledGovernmentsDecisions.begin(),
				exiledGovernmentsDecisions.end(),
				category,
				category
			);
		}
	}
}


bool exiledGovernmentDecisionToUpdate(const std::string& decisionName)
{
	return (decisionName == "purge_infiltrators");
}