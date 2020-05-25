#ifndef INTELLIGENCE_AGENCY_LOGOS_H
#define INTELLIGENCE_AGENCY_LOGOS_H



#include <map>
#include <string>



namespace HoI4
{

class IntelligenceAgencyLogos
{
  public:
	class Factory;
	IntelligenceAgencyLogos(std::map<std::string, std::string>&& cultureToLogoMap): cultureToLogoMap(cultureToLogoMap) {}
	std::string getLogo(const std::string& culture);

  private:
	std::map<std::string, std::string> cultureToLogoMap;
};


class IntelligenceAgencyLogos::Factory
{
  public:
	static IntelligenceAgencyLogos getIntelligenceAgencyLogos();
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_LOGOS_H