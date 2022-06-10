#include "src/V2World/Diplomacy/DiplomacyFactory.h"
#include "src/V2World/Diplomacy/AgreementFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"



Vic2::Diplomacy::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& agreementType, std::istream& theStream) {
		diplomacy->agreements.push_back(*agreementFactory.getAgreement(agreementType, theStream));
	});
}


std::unique_ptr<Vic2::Diplomacy> Vic2::Diplomacy::Factory::getDiplomacy(std::istream& theStream)
{
	diplomacy = std::make_unique<Diplomacy>();
	parseStream(theStream);
	return std::move(diplomacy);
}