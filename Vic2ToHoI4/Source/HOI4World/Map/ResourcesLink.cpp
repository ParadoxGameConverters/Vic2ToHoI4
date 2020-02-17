#include "ResourcesLink.h"
#include "ActualResources.h"
#include "ParserHelpers.h"



ResourcesLink::ResourcesLink(std::istream& theStream)
{
	registerKeyword("province", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt theProvinceNum(theStream);
		provinceNum = theProvinceNum.getInt();
	});
	registerKeyword("resources", [this](const std::string& unused, std::istream& theStream) {
		HoI4::ActualResources theActualResources(theStream);
		theResources = theActualResources.takeResources();
	});
	registerRegex("[a-zA-z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}
