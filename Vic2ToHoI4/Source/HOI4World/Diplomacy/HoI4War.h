#ifndef HOI4_WAR_H
#define HOI4_WAR_H



#include "../../V2World/Wars/War.h"
#include "../../Mappers/CountryMapping.h"
#include <ostream>
#include <set>
#include <string>



namespace HoI4
{

class War
{
	public:
		War(const Vic2::War& sourceWar, const CountryMapper& countryMapper);

		friend std::ostream& operator<<(std::ostream& outstream, const War& theWar);

	private:
		std::string originalDefender;
		std::string CB;
		std::set<std::string> extraDefenders;
		std::string originalAttacker;
		std::set<std::string> extraAttackers;
};


std::ostream& operator<<(std::ostream& outstream, const War& theWar);

}



#endif // HOI4_WAR_H