#include "LanguageReplacements.h"
#include "ParserHelpers.h"



HoI4::LanguageReplacements::LanguageReplacements(std::istream& theStream)
{
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), [this](const std::string& toReplace, std::istream& theStream) {
		commonItems::singleString replaceWithString(theStream);
		replacements.insert(std::make_pair(toReplace, replaceWithString.getString()));
	});

	parseStream(theStream);
}