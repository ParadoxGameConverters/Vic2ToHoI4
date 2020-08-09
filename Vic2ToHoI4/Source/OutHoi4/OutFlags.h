#ifndef OUT_FLAGS_H_
#define OUT_FLAGS_H_



#include "../HOI4World/HoI4Country.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

void copyFlags(const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::string& outputName,
	 const std::vector<Vic2::Mod>& vic2Mods,
	 const std::string& vic2vic2ModPathPath);

}



#endif // OUT_FLAGS_H_