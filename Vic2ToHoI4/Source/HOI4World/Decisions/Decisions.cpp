/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "Decisions.h"
#include "Decision.h"
#include "../Events.h"
#include "../../Configuration.h"
#include <fstream>



HoI4::decisions::decisions() noexcept
{
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		decisionsCategory category(categoryName, theStream);
		stabilityDecisions.push_back(category);
	});
	parseFile("blankmod/output/common/decisions/stability_war_support.txt");

	clearRegisteredKeywords();

	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& ideologyName, std::istream& theStream)
	{
		IdeologicalDecisions ideologicalDecisions(theStream);
		allIdeologicalDecisions.push_back(ideologicalDecisions);
	});
	parseFile("ideologicalDecisions.txt");
}


void HoI4::decisions::updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents)
{
	updateStabilityDecisions(majorIdeologies);
	updatePoliticalDecisions(majorIdeologies, theEvents);

	decisionsCategories = std::make_unique<DecisionsCategories>(majorIdeologies);
}


void HoI4::decisions::updateStabilityDecisions(const std::set<std::string>& majorIdeologies)
{
	auto ideologiesForStabilityDecisions = determineIdeologiesForStabilityDecisions(majorIdeologies);

	for (auto category: stabilityDecisions)
	{
		bool updated = false;
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


bool HoI4::decisions::stabilityDecisionToUpdate(const std::string& decisionName)
{
	if (
			(decisionName == "draft_dodging_mission") || 
			(decisionName == "strikes_mission") || 
			(decisionName == "mutiny_mission") || 
			(decisionName == "demob_economic_mission") || 
			(decisionName == "demob_manpower_mission")
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}


std::pair<std::string, std::string> HoI4::decisions::determineIdeologiesForStabilityDecisions(
	const std::set<std::string>& majorIdeologies
) {
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


std::string HoI4::decisions::updateTimeoutEffect(
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
			for (auto category: ideologicalDecisions.getCategories())
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