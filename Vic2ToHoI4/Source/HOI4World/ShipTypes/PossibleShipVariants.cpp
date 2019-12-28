#include "PossibleShipVariants.h"



HoI4::possibleShipVariants::possibleShipVariants(std::istream& theStream)
{
	registerKeyword(std::regex("ship_type"), [this](const std::string& unused, std::istream& theStream){
		shipVariant theShipVariant(theStream);
		theVariants.push_back(theShipVariant);
	});

	parseStream(theStream);
}