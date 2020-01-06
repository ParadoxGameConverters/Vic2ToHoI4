#include "StateCategoryFile.h"
#include "StateCategory.h"



HoI4::StateCategoryFile::StateCategoryFile(std::istream& theStream)
{
	registerKeyword(std::regex("[a-z\\_]+"), [this](const std::string& categoryName, std::istream& theStream) {
		HoI4::StateCategory category(theStream);
		theCategories.insert(make_pair(category.getNumberOfSlots(), categoryName));
	});

	parseStream(theStream);
}