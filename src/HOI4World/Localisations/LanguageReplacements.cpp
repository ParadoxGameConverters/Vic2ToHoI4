#include "LanguageReplacements.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::LanguageReplacements::LanguageReplacements(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& toReplace, std::istream& theStream) {
		commonItems::singleString replaceWithString(theStream);
		replacements.insert(std::make_pair(toReplace, replaceWithString.getString()));
	});

	parseStream(theStream);
}