#ifndef COUNTRY_LEADER_FACTORY_H
#define COUNTRY_LEADER_FACTORY_H



#include "CountryLeader.h"
#include "HOI4World/Names/Names.h"
#include "Mappers/GraphicsMapper.h"



namespace HoI4
{

class CountryLeader::Factory
{
  public:
	static CountryLeader createNewLeader(const std::string& primaryCulture,
		 const std::string& primaryCultureGroup,
		 const std::string& governmentIdeology,
		 const std::string& leaderIdeology,
		 Names* names,
		 graphicsMapper* theGraphics);
};

} // namespace HoI4



#endif // COUNTRY_LEADER_FACTORY_H