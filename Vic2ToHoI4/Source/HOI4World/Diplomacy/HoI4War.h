#ifndef HOI4_WAR_H
#define HOI4_WAR_H



#include "Mappers/Country/CountryMapping.h"
#include "V2World/Wars/War.h"
#include <ostream>
#include <set>
#include <string>



namespace HoI4
{

class War
{
  public:
	War(const Vic2::War& sourceWar, const CountryMapper& countryMapper);

	friend std::ostream& operator<<(std::ostream& out, const War& theWar);

  private:
	std::string originalDefender;
	std::string CB = "annex_everything";
	std::set<std::string> extraDefenders;
	std::string originalAttacker;
	std::set<std::string> extraAttackers;
};

} // namespace HoI4



#endif // HOI4_WAR_H