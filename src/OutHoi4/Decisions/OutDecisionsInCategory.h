#ifndef OUT_DECISIONS_IN_CATEGORY_H
#define OUT_DECISIONS_IN_CATEGORY_H



#include "src/HOI4World/Decisions/DecisionsInCategory.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const DecisionsInCategory& outCategory);

}



#endif // OUT_DECISIONS_IN_CATEGORY_H