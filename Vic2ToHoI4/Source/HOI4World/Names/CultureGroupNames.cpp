#include "CultureGroupNames.h"
#include "../../../../Fronter/commonItems/ParserHelpers.h"
#include "CultureNames.h"



HoI4::cultureGroup::cultureGroup(std::istream& theStream)
{
	registerKeyword("leader", commonItems::ignoreItem);
	registerKeyword("unit", commonItems::ignoreItem);
	registerKeyword("union", commonItems::ignoreItem);
	registerKeyword("is_overseas", commonItems::ignoreItem);
	registerRegex("[A-Za-z0-9\\_]+", [this](const std::string& cultureName, std::istream& theStream) {
		culture newCulture(theStream);
		newCulture.convertNamesToUTF8();
		maleNamesMap.insert(make_pair(cultureName, newCulture.takeMaleNames()));
		surnamesMap.insert(make_pair(cultureName, newCulture.takeSurnames()));
	});

	parseStream(theStream);
}