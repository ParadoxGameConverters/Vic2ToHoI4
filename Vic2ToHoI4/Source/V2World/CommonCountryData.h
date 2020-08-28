#ifndef COMMON_COUNTRY_DATA_H_
#define COMMON_COUNTRY_DATA_H_



#include "Color.h"
#include "Mods/Mod.h"
#include "Parser.h"
#include "Party.h"
#include <map>
#include <optional>
#include <string>
#include <vector>



class Configuration;



namespace Vic2
{

class commonCountryData: commonItems::parser
{
  public:
	commonCountryData(const std::string& filename, const std::optional<Mod>& mod, const Configuration& theConfiguration);

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