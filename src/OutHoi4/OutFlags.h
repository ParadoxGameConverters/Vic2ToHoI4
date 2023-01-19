#ifndef OUT_FLAGS_H_
#define OUT_FLAGS_H_



#include "external/common_items/ModLoader/ModLoader.h"
#include "src/HOI4World/Countries/UnionCountry.h"
#include "src/HOI4World/HoI4Country.h"
#include <map>
#include <string>



namespace HoI4
{

void copyFlags(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::vector<HoI4::UnionCountry>& union_countries,
	 const std::string& outputName,
	 const Mods& vic2Mods,
	 const std::set<std::string>& majorIdeologies);

} // namespace HoI4



#endif // OUT_FLAGS_H_