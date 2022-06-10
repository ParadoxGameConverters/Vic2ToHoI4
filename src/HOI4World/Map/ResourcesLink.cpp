#include "src/HOI4World/Map/ResourcesLink.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Map/ActualResources.h"



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