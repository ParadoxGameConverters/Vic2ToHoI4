#ifndef INTELLIGENCE_AGENCY_LOGOS_H
#define INTELLIGENCE_AGENCY_LOGOS_H



#include "Parser.h"
#include <map>
#include <random>
#include <string>



namespace HoI4
{

class IntelligenceAgencyLogos
{
  public:
	class Factory;
	explicit IntelligenceAgencyLogos(std::map<std::string, std::string> cultureToLogoMap):
		 cultureToLogoMap(std::move(cultureToLogoMap))
	{
	}
	std::string getLogo(const std::string& culture);

  private:
	std::map<std::string, std::string> cultureToLogoMap;
	std::mt19937 generator;
};


class IntelligenceAgencyLogos::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<IntelligenceAgencyLogos> getIntelligenceAgencyLogos();

  private:
	std::map<std::string, std::string> cultureToLogoMap;
};

} // namespace HoI4



#endif // INTELLIGENCE_AGENCY_LOGOS_H