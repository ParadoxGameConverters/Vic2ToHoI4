#include "ResourcesLink.h"
#include "ActualResources.h"
#include "ParserHelpers.h"



ResourcesLink::ResourcesLink(std::istream& theStream)
{
	registerKeyword(std::regex("province"), [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt theProvinceNum(theStream);
		provinceNum = theProvinceNum.getInt();
	});
	registerKeyword(std::regex("resources"), [this](const std::string& unused, std::istream& theStream) {
		const ActualResources theActualResources(theStream);
		theResources = theActualResources.getResources();
	});
	registerRegex("[a-zA-z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}
