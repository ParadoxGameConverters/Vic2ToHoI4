#ifndef OUT_HOI4_STATE_H
#define OUT_HOI4_STATE_H



#include "../../HOI4World/States/HoI4State.h"
#include <ostream>



namespace HoI4
{

void outputHoI4State(std::ostream& output, const HoI4::State& theState, bool debugEnabled);

}



#endif // OUT_HOI4_STATE_H