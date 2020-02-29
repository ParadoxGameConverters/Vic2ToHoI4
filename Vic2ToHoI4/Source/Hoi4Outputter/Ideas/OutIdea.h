#ifndef OUT_IDEA_H
#define OUT_IDEA_H



#include <ostream>



namespace HoI4
{
	
class Idea;

std::ostream& operator<<(std::ostream& outStream, const HoI4::Idea& outIdea);

}



#endif //OUT_IDEA_H