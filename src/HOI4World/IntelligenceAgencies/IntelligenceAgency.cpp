#include "IntelligenceAgency.h"
#include "src/V2World/Countries/Country.h"



HoI4::IntelligenceAgency::IntelligenceAgency(Country& country,
	 Names& names,
	 IntelligenceAgencyLogos& intelligenceAgencyLogos):
	 countryTag(country.getTag())
{
	const auto possibleName = names.takeIntelligenceAgencyName(country.getPrimaryCulture(), country.getGenerator());
	if (possibleName)
	{
		name = *possibleName;
	}
	else
	{
		name = "Intelligence Agency";
	}
	logo = intelligenceAgencyLogos.getLogo(country.getPrimaryCulture());
}