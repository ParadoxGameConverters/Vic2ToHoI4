#ifndef HOI4_MAP_HOI4PROVINCEDEFINITIONIMPORTER_H
#define HOI4_MAP_HOI4PROVINCEDEFINITIONIMPORTER_H



#include "src/Maps/ProvinceDefinitions.h"



namespace HoI4
{

[[nodiscard]] Maps::ProvinceDefinitions importProvinceDefinitions(const std::string& path);

}



#endif // HOI4_MAP_HOI4PROVINCEDEFINITIONIMPORTER_H