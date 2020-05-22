#ifndef INTELLIGENCE_AGENCY_H
#define INTELLIGENCE_AGENCY_H



#include <string>
#include <vector>



namespace HoI4
{

class IntelligenceAgency
{
  public:
	explicit IntelligenceAgency(std::string country): country(std::move(country)) {}
	
	[[nodiscard]] const auto& getCountry() const { return country; }
	[[nodiscard]] const auto& getLogo() const { return logo; }
	[[nodiscard]] const auto& getNames() const { return names; }

  private:
	std::string country;
	std::string logo = "GFX_intelligence_agency_logo_usa";
	std::vector<std::string> names{"Office of Strategic Services"};
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_H