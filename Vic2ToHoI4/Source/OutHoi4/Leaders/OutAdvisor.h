#ifndef OUT_ADVISOR_H
#define OUT_ADVISOR_H


#include "../../HOI4World/Leaders/Advisor.h"


namespace HoI4
{

void outputAdvisor(std::ostream& output, const std::string& tag, const Advisor& theAdvisor); //see if tag should be in the advisor

}



#endif // OUT_ADVISOR_H