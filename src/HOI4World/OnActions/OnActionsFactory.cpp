#include "src/HOI4World/OnActions/OnActionsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::OnActions::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& key, std::istream& theStream) {
		importedOnActions.emplace(key, commonItems::stringOfItem(theStream).getString());
	});
}


std::multimap<std::string, std::string> HoI4::OnActions::Factory::importOnActions(const std::filesystem::path& filePath)
{
	parseFile(filePath);
	clearRegisteredKeywords();

	return importedOnActions;
}