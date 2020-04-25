#include "DecisionsCategories.h"



HoI4::DecisionsCategories::Factory::Factory()
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& categoryName, std::istream& theStream) {
		theCategories.emplace_back(DecisionsCategoryFactory.getDecisionsCategory(categoryName, theStream));
	});
}


std::unique_ptr<HoI4::DecisionsCategories> HoI4::DecisionsCategories::Factory::getDecisionsCategories()
{
	theCategories.clear();
	return std::make_unique<DecisionsCategories>(theCategories);
}


std::unique_ptr<HoI4::DecisionsCategories> HoI4::DecisionsCategories::Factory::getDecisionsCategories(
	 std::istream& theStream)
{
	theCategories.clear();
	parseStream(theStream);

	return std::make_unique<DecisionsCategories>(theCategories);
}


std::unique_ptr<HoI4::DecisionsCategories> HoI4::DecisionsCategories::Factory::getDecisionsCategories(
	 const std::string& filename)
{
	theCategories.clear();
	parseFile(filename);

	return std::make_unique<DecisionsCategories>(theCategories);
}