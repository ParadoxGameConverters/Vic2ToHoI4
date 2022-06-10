#include "src/HOI4World/States/StateCategories.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"
#include "src/HOI4World/States/StateCategoryFile.h"
#include <set>



HoI4::StateCategories::StateCategories(const Configuration& theConfiguration)
{
	registerKeyword("state_categories", [this](std::istream& theStream) {
		StateCategoryFile theFile(theStream);
		for (auto category: theFile.getCategories())
		{
			theCategories.insert(category);
		}
	});

	for (const auto& file: commonItems::GetAllFilesInFolder(theConfiguration.getHoI4Path() + "/common/state_category"))
	{
		parseFile(theConfiguration.getHoI4Path() + "/common/state_category/" + file);
	}
}


std::string HoI4::StateCategories::getBestCategory(int numBuildingSlots) const
{
	std::string theCategory;
	for (auto possibleCategory: theCategories)
	{
		if (numBuildingSlots >= possibleCategory.first)
		{
			theCategory = possibleCategory.second;
		}
	}

	return theCategory;
}