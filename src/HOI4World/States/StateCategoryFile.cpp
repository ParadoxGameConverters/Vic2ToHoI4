#include "src/HOI4World/States/StateCategoryFile.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/States/StateCategory.h"



HoI4::StateCategoryFile::StateCategoryFile(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& categoryName, std::istream& theStream) {
		HoI4::StateCategory category(theStream);
		theCategories.insert(make_pair(category.getNumberOfSlots(), categoryName));
	});

	parseStream(theStream);
}