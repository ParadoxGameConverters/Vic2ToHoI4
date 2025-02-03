#ifndef OUT_OPERATIVE_NAMES_SET_H
#define OUT_OPERATIVE_NAMES_SET_H



#include "src/HOI4World/OperativeNames/OperativeNamesSet.h"
#include <string>



namespace HoI4
{

void outputOperativeNamesSet(const OperativeNamesSet& operativeNamesSet, const std::filesystem::path& outputName);

}



#endif // OUT_OPERATIVE_NAMES_SET_H