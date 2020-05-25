#ifndef INTELLIGENCE_AGENCY_LOGOS_H
#define INTELLIGENCE_AGENCY_LOGOS_H



#include <map>
#include <string>



namespace HoI4
{

class IntelligenceAgencyLogos
{
  public:
	IntelligenceAgencyLogos(std::map<std::string, std::string>&& cultureToLogoMap): cultureToLogoMap(cultureToLogoMap) {}
	std::string getLogo(const std::string& culture);

  private:
	std::map<std::string, std::string> cultureToLogoMap;
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_LOGOS_H