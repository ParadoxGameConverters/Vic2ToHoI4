#ifndef OUTHOI4_CHARACTERS_OUT_PORTRAIT_H
#define OUTHOI4_CHARACTERS_OUT_PORTRAIT_H



#include "src/HOI4World/Characters/Portrait.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Portrait& portrait);

} // namespace HoI4



#endif // OUTHOI4_CHARACTERS_OUT_PORTRAIT_H