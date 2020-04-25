#include "IdeologicalDecisions.h"
#include "ParserHelpers.h"



HoI4::IdeologicalDecisions::IdeologicalDecisions(std::istream& theStream)
{
	registerKeyword(std::regex("required_ideologies"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList ideologiesStrings(theStream);
		for (const auto& ideology: ideologiesStrings.getStrings())
		{
			requiredIdeologies.insert(ideology);
		}
	});
	registerKeyword(std::regex("[A-Za-z0-9_-]+"), [this](const std::string& categoryName, std::istream& theStream) {
		const DecisionsInCategory category(categoryName, theStream);
		theCategories.push_back(category);
	});
	parseStream(theStream);
}


bool HoI4::IdeologicalDecisions::requiredIdeologiesExist(const std::set<std::string>& majorIdeologies)
{
	for (const auto& requiredIdeology: requiredIdeologies)
	{
		if (majorIdeologies.count(requiredIdeology) == 0)
		{
			return false;
		}
	}

	return true;
}