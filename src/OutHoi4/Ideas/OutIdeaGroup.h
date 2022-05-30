#ifndef OUT_IDEA_GROUP_H
#define OUT_IDEA_GROUP_H



#include "HOI4World/Ideas/IdeaGroup.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const IdeaGroup& outIdeaGroup);

} // namespace HoI4



#endif // OUT_IDEA_GROUP_H