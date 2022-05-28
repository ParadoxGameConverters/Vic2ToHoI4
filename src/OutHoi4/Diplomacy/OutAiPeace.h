#ifndef OUT_AI_PEACE_H
#define OUT_AI_PEACE_H



#include "HOI4World/Diplomacy/AIPeace.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const AiPeace& outPeace);

}



#endif // OUT_AI_PEACE_H