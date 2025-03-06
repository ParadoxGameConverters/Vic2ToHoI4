#ifndef OUT_OPERATIVE_NAMES_H
#define OUT_OPERATIVE_NAMES_H



#include "src/HOI4World/OperativeNames/OperativeNames.h"
#include <string>



namespace HoI4
{

void outputOperativeNames(const OperativeNames& operativeNames, const std::filesystem::path& outputName);

}



#endif // OUT_OPERATIVE_NAMES_H