#ifndef OUT_IDEA_GROUP_H
#define OUT_IDEA_GROUP_H



#include <ostream>



namespace HoI4
{

class IdeaGroup;

std::ostream& operator<<(std::ostream& outStream, const HoI4::IdeaGroup& outIdeaGroup);

}



#endif // OUT_IDEA_GROUP_H