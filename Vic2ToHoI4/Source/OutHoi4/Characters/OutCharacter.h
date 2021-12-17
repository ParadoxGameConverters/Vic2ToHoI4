#ifndef OUTHOI4_CHARACTERS_OUT_CHARACTER_H
#define OUTHOI4_CHARACTERS_OUT_CHARACTER_H



#include "HOI4World/Characters/Character.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Character& character);

}



#endif // OUTHOI4_CHARACTERS_OUT_CHARACTER_H