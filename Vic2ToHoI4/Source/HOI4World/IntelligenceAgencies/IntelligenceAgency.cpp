#include "IntelligenceAgency.h"
#include "../../V2World/Country.h"



HoI4::IntelligenceAgency::IntelligenceAgency(const Country& country, Names& allNames)
{
	countryTag = country.getTag();
	const auto possibleName = allNames.takeIntelligenceAgencyName(country.getSourceCountry().getPrimaryCulture());
	if (possibleName)
	{
		names.push_back(*possibleName);
	}
	else
	{
		names.push_back("Intelligence Agency");
	}
}