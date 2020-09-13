#include "Agreement.h"
#include "ParserHelpers.h"



Vic2::Agreement::Agreement(const std::string& agreementType, std::istream& theStream): type(agreementType)
{
	registerKeyword("first", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString countryString(theStream);
		country1 = countryString.getString();
		if (country1.substr(0, 1) == "\"")
		{
			country1 = country1.substr(1, country1.size() - 2);
		}
	});
	registerKeyword("second", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString countryString(theStream);
		country2 = countryString.getString();
		if (country2.substr(0, 1) == "\"")
		{
			country2 = country2.substr(1, country2.size() - 2);
		}
	});
	registerKeyword("start_date", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString dateString(theStream);
		startDate = date(dateString.getString());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}