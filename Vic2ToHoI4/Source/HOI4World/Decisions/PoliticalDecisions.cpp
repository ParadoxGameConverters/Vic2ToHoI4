#include "PoliticalDecisions.h"



void HoI4::PoliticalDecisions::importDecisions(std::istream& theStream)
{
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const IdeologicalDecisions ideologicalDecisions(theStream);
		allIdeologicalDecisions.push_back(ideologicalDecisions);
	});

	parseStream(theStream);
}


void HoI4::PoliticalDecisions::updateDecisions(const std::set<std::string>& majorIdeologies, const Events& theEvents)
{
	for (auto ideologicalDecisions: allIdeologicalDecisions)
	{
		if (ideologicalDecisions.requiredIdeologiesExist(majorIdeologies))
		{
			for (const auto& category: ideologicalDecisions.getCategories())
			{
				if (
					auto existingCategory = std::find(decisions.begin(), decisions.end(), category);
					existingCategory != decisions.end()
					)
				{
					for (auto& theDecision: category.getDecisions())
					{
						existingCategory->addDecision(theDecision);
					}
				}
				else
				{
					decisions.push_back(category);
				}
			}
		}
	}

	for (auto& decisionsByIdeology: decisions)
	{
		decisionsByIdeology.updatePoliticalDecisions(majorIdeologies, theEvents);
	}
}