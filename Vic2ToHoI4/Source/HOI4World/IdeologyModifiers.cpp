#include "IdeologyModifiers.h"
#include "ParserHelpers.h"



HoI4::IdeologyModifiers::IdeologyModifiers(std::istream& theStream)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& key, std::istream& theStream) {
		const commonItems::stringOfItem valueString(theStream);
		modifiers.insert(std::make_pair(key, valueString.getString()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}