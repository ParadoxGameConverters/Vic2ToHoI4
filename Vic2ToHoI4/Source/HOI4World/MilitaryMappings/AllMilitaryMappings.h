#ifndef ALL_MILITARY_MAPPINGS
#define ALL_MILITARY_MAPPINGS



#include "V2World/Mods/Mod.h"
#include "MilitaryMappings.h"
#include "Parser.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class allMilitaryMappings: commonItems::parser
{
  public:
	explicit allMilitaryMappings(std::istream& theStream);

	[[nodiscard]] const militaryMappings& getMilitaryMappings(const std::vector<Vic2::Mod>& Vic2Mods) const;

  private:
	std::map<std::string, militaryMappings> theMappings;
};

} // namespace HoI4



#endif // ALL_MILITARY_MAPPINGS