#include "IdeologyItems.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::IdeologyItems::IdeologyItems(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& key, std::istream& theStream) {
		const commonItems::stringOfItem valueString(theStream);
		items.insert(std::make_pair(key, valueString.getString()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}