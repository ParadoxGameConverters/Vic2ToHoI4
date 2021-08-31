#include "RebellionFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "StringUtils.h"



Vic2::Rebellion::Factory::Factory()
{
	registerKeyword("country", [this](std::istream& theStream) {
		const auto& countryStr = commonItems::singleString{theStream}.getString();
		rebellion->country = commonItems::remQuotes(countryStr);
	});
	registerKeyword("type", [this](std::istream& theStream) {
		const auto& typeStr = commonItems::singleString{theStream}.getString();
		rebellion->type = commonItems::remQuotes(typeStr);
	});
	registerKeyword("provinces", [this](std::istream& theStream) {
		rebellion->provinces = commonItems::intList(theStream).getInts();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Rebellion> Vic2::Rebellion::Factory::importRebellion(std::istream& theStream)
{
	rebellion = std::make_unique<Rebellion>();
	parseStream(theStream);
	return std::move(rebellion);
}