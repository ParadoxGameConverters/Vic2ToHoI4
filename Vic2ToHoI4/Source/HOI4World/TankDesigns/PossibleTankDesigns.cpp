#include "PossibleTankDesigns.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



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