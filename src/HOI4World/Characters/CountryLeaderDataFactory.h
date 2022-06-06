#ifndef HOI4_CHARACTERS_COUNTRY_LEADER_DATA_FACTORY_H
#define HOI4_CHARACTERS_COUNTRY_LEADER_DATA_FACTORY_H



#include "CountryLeaderData.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace HoI4
{

class CountryLeaderDataFactory: commonItems::parser
{
  public:
	CountryLeaderDataFactory();

	CountryLeaderData importCountryLeaderData(std::istream& input);

  private:
	std::string ideology_;
	std::vector<std::string> traits_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_COUNTRY_LEADER_DATA_FACTORY_H