#include "AgreementFactory.h"
#include "ParserHelpers.h"



Vic2::Agreement::Factory::Factory()
{
	registerKeyword("first", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString countryString(theStream);
		agreement->country1 = countryString.getString();
		if (agreement->country1.substr(0, 1) == "\"")
		{
			agreement->country1 = agreement->country1.substr(1, agreement->country1.size() - 2);
		}
	});
	registerKeyword("second", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString countryString(theStream);
		agreement->country2 = countryString.getString();
		if (agreement->country2.substr(0, 1) == "\"")
		{
			agreement->country2 = agreement->country2.substr(1, agreement->country2.size() - 2);
		}
	});
	registerKeyword("start_date", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString dateString(theStream);
		agreement->startDate = date(dateString.getString());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Agreement> Vic2::Agreement::Factory::getAgreement(const std::string& agreementType,
	 std::istream& theStream)
{
	agreement = std::make_unique<Agreement>();
	agreement->type = agreementType;
	parseStream(theStream);
	return std::move(agreement);
}