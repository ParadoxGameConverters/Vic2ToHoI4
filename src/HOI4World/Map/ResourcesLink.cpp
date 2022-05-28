#include "ResourcesLink.h"
#include "ActualResources.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::ResourcesLink::ResourcesLink(std::istream& theStream)
{
	registerKeyword("province", [this](std::istream& theStream) {
		const commonItems::singleInt theProvinceNum(theStream);
		provinceNum = theProvinceNum.getInt();
	});
	registerKeyword("resources", [this](std::istream& theStream) {
		ActualResources theActualResources(theStream);
		theResources = theActualResources.takeResources();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}