#ifndef INTELLIGENCE_AGENCY_H
#define INTELLIGENCE_AGENCY_H



#include "../HoI4Country.h"
#include "../Names/Names.h"
#include <string>
#include <vector>



namespace HoI4
{

class IntelligenceAgency
{
  public:
	explicit IntelligenceAgency(const Country& country, Names& names);

	[[nodiscard]] const auto& getCountry() const { return countryTag; }
	[[nodiscard]] const auto& getLogo() const { return logo; }
	[[nodiscard]] const auto& getNames() const { return names; }

  private:
	std::string countryTag;
	std::string logo = "GFX_intelligence_agency_logo_usa";
	std::vector<std::string> names;
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_H