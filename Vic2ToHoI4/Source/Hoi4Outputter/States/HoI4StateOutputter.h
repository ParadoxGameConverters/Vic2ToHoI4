#ifndef HOI4_STATE_OUTPUTTER
#define HOI4_STATE_OUTPUTTER



#include "../../HOI4World/States/HoI4State.h"
#include "../../Configuration.h"
#include <ostream>



namespace HoI4
{

void outputHoI4State(std::ostream& output, const HoI4::State& theState, const Configuration& theConfiguration);

}



#endif // HOI4_STATE_OUTPUTTER