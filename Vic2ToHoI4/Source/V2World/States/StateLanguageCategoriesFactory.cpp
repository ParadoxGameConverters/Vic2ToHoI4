#include "StateLanguageCategoriesFactory.h"
#include "ParserHelpers.h"



Vic2::StateLanguageCategories::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& category, std::istream& theStream) {
		const auto states = commonItems::stringList{theStream}.getStrings();
		for (const auto& state: states)
		{
			theCategories->categories[state] = category;
		}
	});
}


std::unique_ptr<Vic2::StateLanguageCategories> Vic2::StateLanguageCategories::Factory::getCategories()
{
	theCategories = std::make_unique<StateLanguageCategories>();
	parseFile("./DataFiles/Localisations/StateCategories.txt");
	return std::move(theCategories);
}