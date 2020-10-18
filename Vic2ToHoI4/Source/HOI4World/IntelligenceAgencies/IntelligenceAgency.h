#ifndef INTELLIGENCE_AGENCY_H
#define INTELLIGENCE_AGENCY_H



#include "HOI4World/HoI4Country.h"
#include "HOI4World/Names/Names.h"
#include "IntelligenceAgencyLogos.h"
#include <string>



namespace HoI4
{

class IntelligenceAgency
{
  public:
	explicit IntelligenceAgency(const Country& country, Names& names, IntelligenceAgencyLogos& intelligenceAgencyLogos);
	explicit IntelligenceAgency(std::string name, std::string logo): logo(std::move(logo)), name(std::move(name)) {}

	[[nodiscard]] const auto& getCountry() const { return countryTag; }
	[[nodiscard]] const auto& getLogo() const { return logo; }
	[[nodiscard]] const auto& getName() const { return name; }

  private:
	std::string countryTag;
	std::string logo;
	std::string name;
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_H