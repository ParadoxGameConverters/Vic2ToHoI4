#ifndef COUNTRY_LEADERS_FACTORY_H
#define COUNTRY_LEADERS_FACTORY_H



#include "CountryLeader.h"
#include "Parser.h"
#include <map>



namespace HoI4
{

class CountryLeadersFactory: commonItems::parser
{
  public:
	std::multimap<std::string, CountryLeader> importCountryLeaders();
};

} // namespace HoI4



#endif // COUNTRY_LEADERS_FACTORY_H