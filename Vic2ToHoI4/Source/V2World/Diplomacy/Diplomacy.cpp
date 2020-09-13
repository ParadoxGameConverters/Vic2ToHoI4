#include "Diplomacy.h"
#include "Agreement.h"
#include "Log.h"
#include "ParserHelpers.h"



Vic2::Diplomacy::Diplomacy(std::istream& theStream)
{
	registerKeyword("vassal", [this](const std::string& agreementType, std::istream& theStream) {
		Agreement* agreement = new Agreement(agreementType, theStream);
		agreements.push_back(agreement);
	});
	registerKeyword("alliance", [this](const std::string& agreementType, std::istream& theStream) {
		Agreement* agreement = new Agreement(agreementType, theStream);
		agreements.push_back(agreement);
	});
	registerKeyword("casus_belli", [this](const std::string& agreementType, std::istream& theStream) {
		Agreement* agreement = new Agreement(agreementType, theStream);
		agreements.push_back(agreement);
	});
	registerKeyword("warsubsidy", [this](const std::string& agreementType, std::istream& theStream) {
		Agreement* agreement = new Agreement(agreementType, theStream);
		agreements.push_back(agreement);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}