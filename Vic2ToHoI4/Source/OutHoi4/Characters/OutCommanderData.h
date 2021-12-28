#ifndef OUTHOI4_CHARACTERS_OUT_COMMANDER_DATA_H
#define OUTHOI4_CHARACTERS_OUT_COMMANDER_DATA_H



#include "HOI4World/Characters/CommanderData.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const CommanderData& commanderData);

} // namespace HoI4



#endif // OUTHOI4_CHARACTERS_OUT_COMMANDER_DATA_H