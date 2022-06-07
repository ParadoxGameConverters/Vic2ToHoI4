#ifndef HOI4_PROVINCES_H
#define HOI4_PROVINCES_H



#include "src/Configuration.h"
#include "Hoi4Province.h"
#include <map>



namespace HoI4
{

[[nodiscard]] std::map<int, Province> importProvinces(const Configuration& theConfiguration);

}



#endif // HOI4_PROVINCES_H