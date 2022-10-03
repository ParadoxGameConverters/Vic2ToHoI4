#include "src/HOI4World/PlaneDesigns/PossiblePlaneDesigns.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PossiblePlaneDesigns::PossiblePlaneDesigns(std::istream& theStream)
{
	registerKeyword("plane_design", [this](std::istream& lambdaRegex) {
		const PlaneDesign thePlaneDesign(lambdaRegex);
		tankDesigns.push_back(thePlaneDesign);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}