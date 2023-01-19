#ifndef SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_FACTORY_H
#define SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/ModLoader/ModLoader.h"
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
	std::unique_ptr<CommonCountryData> ImportCommonCountryData(const std::string& filename,
		 const commonItems::ModFilesystem& mod_filesystem);

  private:
	std::unique_ptr<CommonCountryData> common_country_data_;
	Party::Factory party_factory_;
	UnitNamesFactory unit_names_factory_;
};

} // namespace Vic2



#endif // SRC_V2WORLD_COUNTRIES_COMMON_COUNTRY_DATA_FACTORY_H