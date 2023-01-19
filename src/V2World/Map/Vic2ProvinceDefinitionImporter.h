#ifndef SRC_V2WORLD_MAP_VIC2_PROVINCE_DEFINITION_IMPORTER_H
#define SRC_V2WORLD_MAP_VIC2_PROVINCE_DEFINITION_IMPORTER_H



#include "external/common_items/ModLoader/ModFilesystem.h"
#include "src/Maps/ProvinceDefinitions.h"
#include "src/V2World/Provinces/Province.h"
#include <map>
#include <memory>
#include <string>



namespace Vic2
{

[[nodiscard]] Maps::ProvinceDefinitions ImportProvinceDefinitions(const commonItems::ModFilesystem& mod_filesystem,
	 const std::map<int, std::shared_ptr<Province>>& provinces);

}



#endif // SRC_V2WORLD_MAP_VIC2_PROVINCE_DEFINITION_IMPORTER_H