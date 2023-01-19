#include "src/HOI4World/Decisions/IdeologicalDecisions.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::IdeologicalDecisions::IdeologicalDecisions(std::istream& theStream)
{
	registerKeyword("required_ideologies", [this](std::istream& theStream) {
		const commonItems::stringList ideologiesStrings(theStream);
		for (const auto& ideology: ideologiesStrings.getStrings())
		{
			requiredIdeologies.insert(ideology);
		}
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& categoryName, std::istream& theStream) {
		const DecisionsInCategory category(categoryName, theStream);
		theCategories.push_back(category);
	});
	parseStream(theStream);
}


bool HoI4::IdeologicalDecisions::requiredIdeologiesExist(const std::set<std::string>& majorIdeologies)
{
	for (const auto& requiredIdeology: requiredIdeologies)
	{
		if (!majorIdeologies.contains(requiredIdeology))
		{
			return false;
		}
	}

	return true;
}