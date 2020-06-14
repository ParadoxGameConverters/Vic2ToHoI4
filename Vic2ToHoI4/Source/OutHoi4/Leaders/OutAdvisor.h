#ifndef OUT_ADVISOR_H
#define OUT_ADVISOR_H


#include "../../HOI4World/Leaders/Advisor.h"
#include <ostream>


namespace HoI4
{

void outputAdvisor(std::ostream& output, const std::string& tag, const Advisor& theAdvisor);

}



#endif // OUT_ADVISOR_H