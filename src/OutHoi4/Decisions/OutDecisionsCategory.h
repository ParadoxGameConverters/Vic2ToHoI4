#ifndef OUT_DECISIONS_CATEGORY_H
#define OUT_DECISIONS_CATEGORY_H



#include "src/HOI4World/Decisions/DecisionsCategory.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const DecisionsCategory& decisionsCategory);

}



#endif // OUT_DECISIONS_CATEGORY_H