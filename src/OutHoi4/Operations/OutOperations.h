#ifndef OUT_OPERATIONS_H
#define OUT_OPERATIONS_H



#include "src/Configuration.h"
#include "src/HOI4World/Operations/Operations.h"



namespace HoI4
{

void outputOperations(const Operations& operations, const std::filesystem::path& outputName);

}



#endif // OUT_OPERATIONS_H