#include "IntelligenceAgency.h"
#include "V2World/Country.h"



HoI4::IntelligenceAgency::IntelligenceAgency(const Country& country,
	 Names& names,
	 IntelligenceAgencyLogos& intelligenceAgencyLogos):
	 countryTag(country.getTag())
{
	const auto possibleName = names.takeIntelligenceAgencyName(country.getSourceCountry().getPrimaryCulture());
	if (possibleName)
	{
		name = *possibleName;
	}
	else
	{
		name = "Intelligence Agency";
	}
	logo = intelligenceAgencyLogos.getLogo(country.getSourceCountry().getPrimaryCulture());
}