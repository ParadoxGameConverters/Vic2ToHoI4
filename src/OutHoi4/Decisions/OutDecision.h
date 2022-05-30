#ifndef OUT_DECISION_H
#define OUT_DECISION_H


#include "HOI4World/Decisions/Decision.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const decision& outDecision);

}



#endif // OUT_DECISION_H