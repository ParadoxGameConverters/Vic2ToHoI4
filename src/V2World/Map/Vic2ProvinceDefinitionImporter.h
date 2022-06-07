#ifndef VIC2_MAP_VIC2PROVINCEDEFINITIONIMPORTER_H
#define VIC2_MAP_VIC2PROVINCEDEFINITIONIMPORTER_H



#include "src/Maps/ProvinceDefinitions.h"
#include "src/V2World/Provinces/Province.h"
#include <map>
#include <memory>
#include <string>



namespace Vic2
{

[[nodiscard]] Maps::ProvinceDefinitions importProvinceDefinitions(const std::string& path,
	 const std::map<int, std::shared_ptr<Province>>& provinces);

}



#endif // VIC2_MAP_VIC2PROVINCEDEFINITIONIMPORTER_H