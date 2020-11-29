#ifndef COMMON_COUNTRY_DATA_H_
#define COMMON_COUNTRY_DATA_H_



#include "Color.h"
#include "Configuration.h"
#include "Parser.h"
#include "V2World/Mods/Mod.h"
#include "V2World/Politics/Party.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class CommonCountryData: commonItems::parser
{
  public:
	class Factory;
	CommonCountryData() = default;

	auto getColor() { return std::move(theColor); }
	auto getUnitNames() { return std::move(unitNames); }
	auto getParties() { return std::move(parties); }

  private:
	commonItems::Color theColor;
	std::map<std::string, std::vector<std::string>> unitNames;
	std::vector<Party> parties;
};

} // namespace Vic2



#endif // COMMON_COUNTRY_DATA_H_