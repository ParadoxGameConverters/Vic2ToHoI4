#include "src/HOI4World/Names/CultureGroupNames.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Names/CultureNames.h"



HoI4::CultureGroupNames::CultureGroupNames(std::istream& theStream)
{
	registerKeyword("leader", commonItems::ignoreItem);
	registerKeyword("unit", commonItems::ignoreItem);
	registerKeyword("union", commonItems::ignoreItem);
	registerKeyword("is_overseas", commonItems::ignoreItem);
	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureName, std::istream& theStream) {
		CultureNames cultureNames(theStream);
		cultureNames.convertVic2NamesToUTF8();
		maleNamesMap.insert(make_pair(cultureName, cultureNames.takeMaleNames()));
		surnamesMap.insert(make_pair(cultureName, cultureNames.takeSurnames()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}