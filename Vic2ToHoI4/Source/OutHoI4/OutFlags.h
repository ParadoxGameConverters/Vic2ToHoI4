#ifndef OUT_FLAGS_H_
#define OUT_FLAGS_H_



#include "../HOI4World/HoI4Country.h"
#include <map>
#include <string>



void copyFlags(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries, const std::string& outputName);



#endif // OUT_FLAGS_H_