#ifndef INTELLIGENCE_AGENCY_LOGO_MAPPING_H
#define INTELLIGENCE_AGENCY_LOGO_MAPPING_H



#include "Parser.h"
#include <string>
#include <vector>



namespace HoI4
{

class IntelligenceAgencyLogoMapping: commonItems::parser
{
  public:
	IntelligenceAgencyLogoMapping(std::istream& theStream);
	
	[[nodiscard]] auto&& takeLogo() { return std::move(logo); }
	[[nodiscard]] auto&& takeCultures() { return std::move(cultures); }

  private:
	std::string logo = "GFX_intelligence_agency_logo_generic_1";
	std::vector<std::string> cultures;
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_LOGO_MAPPING_H