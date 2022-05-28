#ifndef OUT_IDEA_H
#define OUT_IDEA_H



#include "HOI4World/Ideas/Idea.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const Idea& outIdea);

} // namespace HoI4



#endif // OUT_IDEA_H