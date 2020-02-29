#ifndef OUT_IDEA_H
#define OUT_IDEA_H



#include <ostream>



namespace HoI4
{

class Idea;

std::ostream& operator<<(std::ostream& outStream, const Idea& outIdea);

} // namespace HoI4



#endif // OUT_IDEA_H