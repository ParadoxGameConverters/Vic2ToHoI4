#ifndef OUT_HOI4_CHARACTERS_OUT_COUNTRY_LEADER_DATA_H
#define OUT_HOI4_CHARACTERS_OUT_COUNTRY_LEADER_DATA_H



#include "HOI4World/Characters/CountryLeaderData.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const CountryLeaderData& countryLeaderData);

} // namespace HoI4



#endif // OUT_HOI4_CHARACTERS_OUT_COUNTRY_LEADER_DATA_H