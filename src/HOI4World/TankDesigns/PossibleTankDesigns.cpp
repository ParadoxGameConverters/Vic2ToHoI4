#include "PossibleTankDesigns.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::PossibleTankDesigns::PossibleTankDesigns(std::istream& theStream)
{
	registerKeyword("tank_design", [this](std::istream& theStream) {
		const TankDesign theTankDesign(theStream);
		tankDesigns.push_back(theTankDesign);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}