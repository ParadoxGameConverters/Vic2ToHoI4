#ifndef COUNTRY_LEADER_FACTORY_H
#define COUNTRY_LEADER_FACTORY_H



#include "CountryLeader.h"
#include "HOI4World/Names/Names.h"
#include "Mappers/Graphics/GraphicsMapper.h"
#include "Parser.h"
#include <memory>



namespace HoI4
{

class CountryLeader::Factory: commonItems::parser
{
  public:
	Factory();

	static CountryLeader createNewLeader(const std::string& primaryCulture,
		 const std::string& primaryCultureGroup,
		 const std::string& governmentIdeology,
		 const std::string& leaderIdeology,
		 Names& names,
		 graphicsMapper& theGraphics);
	std::unique_ptr<CountryLeader> importCountryLeader(std::istream& theStream);

  private:
	std::unique_ptr<CountryLeader> countryLeader;
};

} // namespace HoI4



#endif // COUNTRY_LEADER_FACTORY_H