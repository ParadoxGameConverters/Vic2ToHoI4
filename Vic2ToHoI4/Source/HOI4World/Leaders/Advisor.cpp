#include "Advisor.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::Advisor::Advisor(std::string ideology, std::istream& theStream): ideology(std::move(ideology))
{
	registerKeyword("traits", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList traitString(theStream);
		traits = traitString.getStrings();
	});
	registerKeyword("picture", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString pictureString(theStream);
		picture = pictureString.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}