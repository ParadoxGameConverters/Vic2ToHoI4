#ifndef SRC_OUT_HOI4_COUNTRIES_OUT_UNION_COUNTRY_H_
#define SRC_OUT_HOI4_COUNTRIES_OUT_UNION_COUNTRY_H_



#include "src/HOI4World/Countries/UnionCountry.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const UnionCountry& country);

}



#endif // SRC_OUT_HOI4_COUNTRIES_OUT_UNION_COUNTRY_H_