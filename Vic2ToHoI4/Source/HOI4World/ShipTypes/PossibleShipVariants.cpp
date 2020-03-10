#include "PossibleShipVariants.h"
#include "ParserHelpers.h"



HoI4::PossibleShipVariants::PossibleShipVariants(std::istream& theStream)
{
	registerKeyword("mtg_ship_type", [this](const std::string& unused, std::istream& theStream) {
		const MtgShipVariant theShipVariant(theStream);
		mtgVariants.push_back(theShipVariant);
	});
	registerKeyword("legacy_ship_type", [this](const std::string& unused, std::istream& theStream) {
		const LegacyShipVariant theShipVariant(theStream);
		legacyVariants.push_back(theShipVariant);
	});
	registerRegex("[a-zA-Z0-9_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}