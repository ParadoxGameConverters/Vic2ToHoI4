#include "CountryLeaderDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::CountryLeaderDataFactory::CountryLeaderDataFactory()
{
	registerKeyword("ideology", [this](std::istream& input) {
		ideology_ = commonItems::getString(input);
	});
	registerKeyword("traits", [this](std::istream& input) {
		traits_ = commonItems::getStrings(input);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


HoI4::CountryLeaderData HoI4::CountryLeaderDataFactory::importCountryLeaderData(std::istream& input)
{
	ideology_.clear();
	traits_.clear();
	parseStream(input);
	return CountryLeaderData(ideology_, traits_);
}