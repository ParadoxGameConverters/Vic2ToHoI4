#include "DecisionsFile.h"



void HoI4::DecisionsFile::importDecisions(const std::string& filename)
{
	registerKeyword(std::regex("[A-Za-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream)
	{
		const decisionsCategory category(categoryName, theStream);

		auto categoryMerged = false;
		for (auto& oldCategory: decisions)
		{
			if (oldCategory.getName() == category.getName())
			{
				for (auto decision : category.getDecisions())
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