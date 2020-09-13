#include "DiplomacyFactory.h"
#include "AgreementFactory.h"
#include "Log.h"
#include "ParserHelpers.h"



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