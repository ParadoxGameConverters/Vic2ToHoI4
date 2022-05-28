#include "LanguageReplacements.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::LanguageReplacements::LanguageReplacements(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& toReplace, std::istream& theStream) {
		commonItems::singleString replaceWithString(theStream);
		replacements.insert(std::make_pair(toReplace, replaceWithString.getString()));
	});

	parseStream(theStream);
}