#ifndef OUT_FLAGS_H_
#define OUT_FLAGS_H_



#include "HOI4World/HoI4Country.h"
#include "ModLoader/ModLoader.h"
#include <map>
#include <string>


namespace HoI4
{

void copyFlags(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName,
	 const Mods& vic2Mods);

}



#endif // OUT_FLAGS_H_