#ifndef OUT_HOI4_STATE_H
#define OUT_HOI4_STATE_H



#include "src/HOI4World/States/HoI4State.h"



namespace HoI4
{

void outputHoI4State(std::ostream& output, const State& theState, bool debugEnabled);

}



#endif // OUT_HOI4_STATE_H