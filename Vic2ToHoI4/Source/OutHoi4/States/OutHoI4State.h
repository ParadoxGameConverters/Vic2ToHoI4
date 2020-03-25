#ifndef OUT_HOI4_STATE_H
#define OUT_HOI4_STATE_H



#include "../../Configuration.h"
#include "../../HOI4World/States/HoI4State.h"
#include <ostream>



namespace HoI4
{

void outputHoI4State(std::ostream& output, const HoI4::State& theState, const Configuration& theConfiguration);

}



#endif // OUT_HOI4_STATE_H