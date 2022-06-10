#include "src/V2World/Diplomacy/AgreementFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "external/common_items/StringUtils.h"



Vic2::Agreement::Factory::Factory()
{
	registerKeyword("first", [this](std::istream& theStream) {
		agreement->country1 = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("second", [this](std::istream& theStream) {
		agreement->country2 = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("start_date", [this](std::istream& theStream) {
		agreement->startDate = date(commonItems::singleString{theStream}.getString());
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