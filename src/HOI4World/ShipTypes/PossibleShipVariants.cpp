#include "PossibleShipVariants.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::PossibleShipVariants::PossibleShipVariants(std::istream& theStream)
{
	registerKeyword("mtg_ship_type", [this](std::istream& theStream) {
		const MtgShipVariant theShipVariant(theStream);
		mtgVariants.push_back(theShipVariant);
	});
	registerKeyword("legacy_ship_type", [this](std::istream& theStream) {
		const LegacyShipVariant theShipVariant(theStream);
		legacyVariants.push_back(theShipVariant);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}