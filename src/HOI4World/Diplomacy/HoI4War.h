#ifndef HOI4_WAR_H
#define HOI4_WAR_H



#include "Mappers/CasusBelli/CasusBellis.h"
#include "Mappers/Country/CountryMapper.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "V2World/Wars/War.h"
#include <optional>
#include <set>
#include <string>



namespace HoI4
{

class War
{
  public:
	War(const Vic2::War& sourceWar,
		 const std::set<std::string>& independentCountries,
		 const Mappers::CountryMapper& countryMapper,
		 const Mappers::CasusBellis& casusBellis,
		 const Mappers::ProvinceMapper& provinceMapper,
		 const std::map<int, int>& provinceToStateIDMap);

	friend std::ostream& operator<<(std::ostream& out, const War& theWar);

  private:
	std::string originalDefender;
	std::string CB = "annex_everything";
	std::set<std::string> extraDefenders;
	std::string originalAttacker;
	std::set<std::string> extraAttackers;
	std::optional<int> state;
};

} // namespace HoI4



#endif // HOI4_WAR_H