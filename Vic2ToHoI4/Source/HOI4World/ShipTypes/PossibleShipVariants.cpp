#include "PossibleShipVariants.h"
#include "ParserHelpers.h"



HoI4::possibleShipVariants::possibleShipVariants(std::istream& theStream)
{
	registerKeyword("ship_type", [this](const std::string& unused, std::istream& theStream) {
		const MtgShipVariant theShipVariant(theStream);
		mtgVariants.push_back(theShipVariant);
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}