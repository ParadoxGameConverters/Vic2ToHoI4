#include "src/HOI4World/PlaneDesigns/PossiblePlaneDesigns.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PossiblePlaneDesigns::PossiblePlaneDesigns(std::istream& the_stream)
{
	registerKeyword("plane_design", [this](std::istream& lambda_regex) {
		plane_designs_.emplace_back(lambda_regex);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(the_stream);
	clearRegisteredKeywords();
}