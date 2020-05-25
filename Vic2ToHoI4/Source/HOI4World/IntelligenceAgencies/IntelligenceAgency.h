#ifndef INTELLIGENCE_AGENCY_H
#define INTELLIGENCE_AGENCY_H



#include "../HoI4Country.h"
#include "../Names/Names.h"
#include "IntelligenceAgencyLogos.h"
#include <string>



namespace HoI4
{

class IntelligenceAgency
{
  public:
	explicit IntelligenceAgency(const Country& country, Names& names, IntelligenceAgencyLogos& intelligenceAgencyLogos);

	[[nodiscard]] const auto& getCountry() const { return countryTag; }
	[[nodiscard]] const auto& getLogo() const { return logo; }
	[[nodiscard]] const auto& getName() const { return name; }

  private:
	std::string countryTag;
	std::string logo = "GFX_intelligence_agency_logo_generic_1";
	std::string name;
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_H