#include "src/HOI4World/States/StateCategoryFile.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/States/StateCategory.h"



HoI4::StateCategoryFile::StateCategoryFile(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& categoryName, std::istream& theStream) {
		HoI4::StateCategory category(categoryName, theStream);
		theCategories.push_back(category);
	});

	parseStream(theStream);
}