#ifndef COMMON_COUNTRY_DATA_FACTORY_H
#define COMMON_COUNTRY_DATA_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "external/common_items/ModLoader/ModLoader.h"
#include "src/Configuration.h"
#include "src/V2World/Countries/CommonCountryData.h"
#include "src/V2World/Countries/UnitNamesFactory.h"
#include "src/V2World/Politics/PartyFactory.h"
#include <memory>


namespace Vic2
{

class CommonCountryData::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CommonCountryData> importCommonCountryData(const std::string& filename,
		 const Mods& vic2Mods,
		 const Configuration& theConfiguration);

  private:
	std::unique_ptr<CommonCountryData> commonCountryData;
	Party::Factory partyFactory;
	UnitNamesFactory unitNamesFactory;
};

} // namespace Vic2



#endif // COMMON_COUNTRY_DATA_FACTORY_H