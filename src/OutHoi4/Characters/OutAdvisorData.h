#ifndef OUT_HOI4_WORLD_CHARACTERS_OUT_ADVISOR_DATA_H
#define OUT_HOI4_WORLD_CHARACTERS_OUT_ADVISOR_DATA_H



#include "src/HOI4World/Characters/AdvisorData.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const AdvisorData& admiral_data);

} // namespace HoI4



#endif // OUT_HOI4_WORLD_CHARACTERS_OUT_ADVISOR_DATA_H