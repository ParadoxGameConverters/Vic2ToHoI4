#ifndef OUT_MONARCH_INTERFACE_H
#define OUT_MONARCH_INTERFACE_H



#include "HOI4World/HoI4Country.h"
#include <map>
#include <memory>
#include <string>



namespace HoI4
{

void outMonarchInterface(const std::string& outputFolder,
	 const std::map<std::string, std::shared_ptr<Country>>& countries);

}



#endif // OUT_MONARCH_INTERFACE_H