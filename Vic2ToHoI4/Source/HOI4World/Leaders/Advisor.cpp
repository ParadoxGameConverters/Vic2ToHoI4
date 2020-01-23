#include "Advisor.h"
#include "ParserHelpers.h"



HoI4::Advisor::Advisor(const std::string& ideology, std::istream& theStream):
	ideology(ideology)
{
	registerKeyword(std::regex("traits"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::stringList traitString(theStream);
		traits = traitString.getStrings();
	});
	registerKeyword(std::regex("picture"), [this](const std::string& unused, std::istream& theStream){
		const commonItems::singleString pictureString(theStream);
		picture = pictureString.getString();
	});
	registerKeyword(std::regex("[A-Za-z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}