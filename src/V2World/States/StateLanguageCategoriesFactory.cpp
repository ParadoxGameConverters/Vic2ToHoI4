#include "StateLanguageCategoriesFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::StateLanguageCategories::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& category, std::istream& theStream) {
		for (const auto& state: commonItems::stringList{theStream}.getStrings())
		{
			theCategories->categories[state] = category;
		}
	});
}


std::unique_ptr<Vic2::StateLanguageCategories> Vic2::StateLanguageCategories::Factory::getCategories()
{
	theCategories = std::make_unique<StateLanguageCategories>();
	parseFile("./Configurables/Localisations/StateCategories.txt");
	return std::move(theCategories);
}