#ifndef COMMON_COUNTRY_DATA_FACTORY_H
#define COMMON_COUNTRY_DATA_FACTORY_H



#include "CommonCountryData.h"
#include "Configuration.h"
#include "Parser.h"
#include "UnitNamesFactory.h"
#include "V2World/Politics/PartyFactory.h"
#include <memory>



namespace Vic2
{

class CommonCountryData::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CommonCountryData> importCommonCountryData(const std::string& filename,
		 const std::vector<Vic2::Mod>& vic2Mods,
		 const Configuration& theConfiguration);

  private:
	std::unique_ptr<CommonCountryData> commonCountryData;
	Party::Factory partyFactory;
	UnitNamesFactory unitNamesFactory;
};

} // namespace Vic2



#endif // COMMON_COUNTRY_DATA_FACTORY_H