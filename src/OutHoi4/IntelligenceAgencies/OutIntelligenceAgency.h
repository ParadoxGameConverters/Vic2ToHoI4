#ifndef OUT_INTELLIGENCE_AGENCY
#define OUT_INTELLIGENCE_AGENCY



#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgency.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& output, const IntelligenceAgency& intelligenceAgency);

}



#endif // OUT_INTELLIGENCE_AGENCY