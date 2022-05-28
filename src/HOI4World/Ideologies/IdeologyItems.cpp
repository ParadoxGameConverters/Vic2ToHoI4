#include "IdeologyItems.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::IdeologyItems::IdeologyItems(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& key, std::istream& theStream) {
		const commonItems::stringOfItem valueString(theStream);
		items.insert(std::make_pair(key, valueString.getString()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}