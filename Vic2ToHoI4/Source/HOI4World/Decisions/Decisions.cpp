#include "Decisions.h"
#include "Decision.h"
#include "../Events.h"
#include <sstream>
#include <regex>



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

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		foreignInfluenceDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/foreign_influence.txt");

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);

		auto categoryMerged = false;
		for (auto& oldCategory: foreignInfluenceDecisions)
		{
			if (oldCategory.getName() == category.getName())
			{
				for (auto decision: category.getDecisions())
				{
					oldCategory.addDecision(decision);
				}
				categoryMerged = true;
			}
		}

		if (!categoryMerged)
		{
			foreignInfluenceDecisions.push_back(category);
		}
	});
	parseFile("DataFiles/foreignInfluenceDecisions.txt");

	clearRegisteredKeywords();
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);
		mtgNavalTreatyDecisions.push_back(category);
	});
	parseFile(theConfiguration.getHoI4Path() + "/common/decisions/MTG_naval_treaty.txt");
}


void HoI4::decisions::updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents)
{
	updateStabilityDecisions(majorIdeologies);
	updatePoliticalDecisions(majorIdeologies, theEvents);
	updateExiledGovernmentDecisions(majorIdeologies);
	updateForeignInfluenceDecisions(majorIdeologies);
	updateMtgNavalTreatyDecisions(majorIdeologies);

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


std::regex createIdeologyRegex(const std::set<std::string>& majorIdeologies);


void HoI4::decisions::updateForeignInfluenceDecisions(const std::set<std::string>& majorIdeologies)
{
	const auto ideologyRegex = createIdeologyRegex(majorIdeologies);
	for (auto& category: foreignInfluenceDecisions)
	{
		std::smatch ideologyMatch;
		auto decisions = category.getDecisions();
		decisions.erase(
			std::remove_if(
				decisions.begin(),
				decisions.end(),
				[&ideologyMatch, &ideologyRegex](auto& decision)
				{
					auto visible = decision.getVisible();
					return !std::regex_search(visible, ideologyMatch, ideologyRegex);
				}
			),
			decisions.end());
		category.replaceDecisions(decisions);

		for (auto decision: category.getDecisions())
		{
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
	std::string regexString{ "(" };
	for (const auto& ideology: majorIdeologies)
	{
		regexString += ideology + "|";
	}
	regexString.pop_back();
	regexString += ")";
	return std::regex{ regexString };
}


void HoI4::decisions::updateMtgNavalTreatyDecisions(const std::set<std::string>& majorIdeologies)
{
	for (auto& decisionsCategory : mtgNavalTreatyDecisions)
	{
		for (auto decision: decisionsCategory.getDecisions())
		{
			if (
					(decision.getName() == "MTG_abandon_treaty_democratic") &&
					(majorIdeologies.count("democratic") == 0)
				)
			{
				std::string newVisible = "= {\n";
				newVisible += "\t\t\thas_naval_treaty_trigger = yes\n";
				newVisible += "\t\t\tOR = { \n";
				newVisible += "\t\t\t\thas_government = neutrality\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);
				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_abandon_treaty_fascist")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 1\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newVisible = "= {\n";
				newVisible += "\t\t\thas_naval_treaty_trigger = yes\n";
				newVisible += "\t\t\tOR = { \n";
				for (const auto& ideology: majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					newVisible += "\t\t\t\thas_government = " + ideology + "\n";
				}
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_cheat_on_treaty")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 0\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newVisible = "= {\n";
				newVisible += "\t\t\tOR = {\n";
				newVisible += "\t\t\t\thas_idea = MTG_naval_treaty_adherent\n";
				newVisible += "\t\t\t\thas_idea = MTG_naval_treaty_adherent_reduced\n";
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t\tOR = {\n";
				for (const auto& ideology : majorIdeologies)
				{
					if ((ideology == "democratic") || (ideology == "neutrality"))
					{
						continue;
					}
					newVisible += "\t\t\t\thas_government = " + ideology + "\n";
				}
				newVisible += "\t\t\t}\n";
				newVisible += "\t\t}";
				decision.setVisible(newVisible);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_invite_FROM_to_treaty")
			{
				std::string newAiWillDo = "= {\n";
				newAiWillDo += "\t\t\tfactor = 3\n";
				if (majorIdeologies.count("democratic") > 0)
				{
					newAiWillDo += "\t\t\tmodifier = {\n";
					newAiWillDo += "\t\t\t\thas_government = democratic\n";
					newAiWillDo += "\t\t\t\tadd = 10\n";
					newAiWillDo += "\t\t\t}\n";
				}
				newAiWillDo += "\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = { \n";
				newTargetTrigger += "\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger += "\t\t\t\tNOT = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger += "\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger += "\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\tsize > 15\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM_previous_signatory")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 10\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = { \n";
				newTargetTrigger += "\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\thas_country_flag = MTG_naval_treaty_abandoned\n";
				newTargetTrigger += "\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\tsize > 20\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_send_treaty_warning_to_FROM")
			{
				std::string newAiWillDo = "= {\n\t\t\tfactor = 10\n\t\t}";
				decision.setAiWillDo(newAiWillDo);

				std::string newTargetTrigger = "= {\n";
				newTargetTrigger += "\t\t\tFROM = {\n";
				newTargetTrigger += "\t\t\t\tOR = {\n";
				newTargetTrigger += "\t\t\t\t\tAND = {\n";
				newTargetTrigger += "\t\t\t\t\t\thas_war = no\n";
				newTargetTrigger += "\t\t\t\t\t\tnot = { has_country_flag = MTG_naval_treaty_abandoned }\n";
				newTargetTrigger += "\t\t\t\t\t\tNOT = { has_country_flag = MTG_refused_naval_treaty }\n";
				newTargetTrigger += "\t\t\t\t\t\thas_naval_treaty_trigger = no\n";
				newTargetTrigger += "\t\t\t\t\t\thas_navy_size = { \n";
				newTargetTrigger += "\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger += "\t\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\tAND = {\n";
				newTargetTrigger += "\t\t\t\t\t\thas_naval_treaty_trigger = yes\n";
				newTargetTrigger += "\t\t\t\t\t\thas_navy_size = {\n";
				newTargetTrigger += "\t\t\t\t\t\t\ttype = capital_ship\n";
				newTargetTrigger += "\t\t\t\t\t\t\tsize > 50\n";
				newTargetTrigger += "\t\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t\t}\n";
				newTargetTrigger += "\t\t\t}\n";
				newTargetTrigger += "\t\t}";
				decision.setTargetTrigger(newTargetTrigger);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\tsize < 20\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
			else if (decision.getName() == "MTG_treaty_reduction_signatory_mission")
			{
				std::string newAvailable = "= {\n";
				newAvailable += "\t\t\thas_navy_size = {\n";
				newAvailable += "\t\t\t\ttype = capital_ship\n";
				newAvailable += "\t\t\t\tsize < 50\n";
				newAvailable += "\t\t\t}\n";
				newAvailable += "\t\t}";
				decision.setAvailable(newAvailable);

				decisionsCategory.replaceDecision(decision);
			}
		}
	}
}