#include "IntelligenceAgencyLogoMapping.h"
#include "ParserHelpers.h"



HoI4::IntelligenceAgencyLogoMapping::IntelligenceAgencyLogoMapping(std::istream& theStream)
{
	registerKeyword("culture", [this](const std::string& unused, std::istream& theStream) {
		cultures.push_back(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("logo", [this](const std::string& unused, std::istream& theStream) {
		logo = commonItems::singleString{theStream}.getString();
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}