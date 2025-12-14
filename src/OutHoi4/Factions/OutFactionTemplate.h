#ifndef OUTHOI4_FACTION_TEMPLATE_H
#define OUTHOI4_FACTION_TEMPLATE_H



#include "src/HOI4World/Factions/FactionTemplate.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const FactionTemplate& theTemplate);

} // namespace HoI4



#endif // OUTHOI4_FACTION_TEMPLATE_H