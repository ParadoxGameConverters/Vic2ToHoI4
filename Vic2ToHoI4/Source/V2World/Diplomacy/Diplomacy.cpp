#include "Diplomacy.h"
#include "Agreement.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "AgreementFactory.h"



Vic2::Diplomacy::Diplomacy(std::istream& theStream)
{
	auto agreementFactory = Agreement::Factory{};
	registerKeyword("vassal", [this, &agreementFactory](const std::string& agreementType, std::istream& theStream) {
		auto agreement = agreementFactory.getAgreement(agreementType, theStream);
		agreements.push_back(*agreement);
	});
	registerKeyword("alliance", [this, &agreementFactory](const std::string& agreementType, std::istream& theStream) {
		auto agreement = agreementFactory.getAgreement(agreementType, theStream);
		agreements.push_back(*agreement);
	});
	registerKeyword("casus_belli", [this, &agreementFactory](const std::string& agreementType, std::istream& theStream) {
		auto agreement = agreementFactory.getAgreement(agreementType, theStream);
		agreements.push_back(*agreement);
	});
	registerKeyword("warsubsidy", [this, &agreementFactory](const std::string& agreementType, std::istream& theStream) {
		auto agreement = agreementFactory.getAgreement(agreementType, theStream);
		agreements.push_back(*agreement);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}