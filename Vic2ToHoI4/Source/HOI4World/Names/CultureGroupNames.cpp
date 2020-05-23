#include "CultureGroupNames.h"
#include "../../../../Fronter/commonItems/ParserHelpers.h"
#include "CultureNames.h"



HoI4::CultureGroupNames::CultureGroupNames(std::istream& theStream)
{
	registerKeyword("leader", commonItems::ignoreItem);
	registerKeyword("unit", commonItems::ignoreItem);
	registerKeyword("union", commonItems::ignoreItem);
	registerKeyword("is_overseas", commonItems::ignoreItem);
	registerRegex("[A-Za-z0-9\\_]+", [this](const std::string& cultureName, std::istream& theStream) {
		CultureNames cultureNames(theStream);
		cultureNames.convertNamesToUTF8();
		maleNamesMap.insert(make_pair(cultureName, cultureNames.takeMaleNames()));
		surnamesMap.insert(make_pair(cultureName, cultureNames.takeSurnames()));
	});

	parseStream(theStream);
}