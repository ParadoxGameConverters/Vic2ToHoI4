#ifndef OUT_COUNTRY_LEADER_H
#define OUT_COUNTRY_LEADER_H



#include "HOI4World/Leaders/CountryLeader.h"
#include <ostream>



namespace HoI4
{

void outputCountryLeader(std::ostream& output, const CountryLeader& leader);

}



#endif // OUT_COUNTRY_LEADER_H