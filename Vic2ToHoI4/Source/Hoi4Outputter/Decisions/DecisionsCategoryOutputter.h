#ifndef DECISIONS_CATEGORY_OUTPUTTER
#define DECISIONS_CATEGORY_OUTPUTTER



#include "../../HOI4World/Decisions/DecisionsCategory.h"
#include <ostream>



namespace HoI4
{
std::ostream& operator<<(std::ostream& outStream, const decisionsCategory& outCategory);
}



#endif // DECISIONS_CATEGORY_OUTPUTTER