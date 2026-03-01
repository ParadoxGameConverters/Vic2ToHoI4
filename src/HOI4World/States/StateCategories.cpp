#include "src/HOI4World/States/StateCategories.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/Configuration.h"
#include "src/HOI4World/States/StateCategoryFile.h"
#include <algorithm>
#include <ranges>
#include <set>



HoI4::StateCategories::StateCategories(const Configuration& theConfiguration)
{
	registerKeyword("state_categories", [this](std::istream& theStream) {
		StateCategoryFile theFile(theStream);
		for (auto category: theFile.getCategories())
		{
			theCategories.push_back(category);
		}
	});

	for (const auto& file: commonItems::GetAllFilesInFolder(theConfiguration.getHoI4Path() / "common/state_category"))
	{
		parseFile(theConfiguration.getHoI4Path() / "common/state_category" / file);
	}
}


HoI4::StateCategory HoI4::StateCategories::getBestCategory(int numBuildingSlots, int navalBaseLevel) const
{
	static const StateCategory fallback;

	auto fits = [numBuildingSlots, navalBaseLevel](const StateCategory& c) {
		return c.getNumberOfSlots() <= numBuildingSlots && c.getBuildingMaxLevel("naval_base") >= navalBaseLevel;
	};

	auto filtered = theCategories | std::views::filter(fits);

	auto it = std::ranges::max_element(filtered, {}, &StateCategory::getNumberOfSlots);

	if (it == std::ranges::end(filtered))
		return fallback;

	return *it;
}