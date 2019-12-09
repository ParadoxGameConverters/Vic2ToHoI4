#ifndef DECISION_OUTPUTTER_H
#define DECISION_OUTPUTTER_H


#include "../Vic2ToHoI4/Source/HOI4World/Decisions/Decision.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator<<(std::ostream& outStream, const decision& outDecision);
}




#endif // DECISION_OUTPUTTER_H