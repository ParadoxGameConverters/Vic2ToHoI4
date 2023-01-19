#ifndef OUTHOI4_CHARACTERS_OUT_CHARACTER_H
#define OUTHOI4_CHARACTERS_OUT_CHARACTER_H



#include "src/HOI4World/Characters/Character.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Character& character);

} // namespace HoI4



#endif // OUTHOI4_CHARACTERS_OUT_CHARACTER_H