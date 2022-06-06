#include "DecisionsFile.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



void HoI4::DecisionsFile::importDecisions(const std::string& filename)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& categoryName, std::istream& theStream) {
		const DecisionsInCategory category(categoryName, theStream);

		auto categoryMerged = false;
		for (auto& oldCategory: decisions)
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
			decisions.push_back(category);
		}
	});

	parseFile(filename);
}