#ifndef ALL_MILITARY_MAPPINGS
#define ALL_MILITARY_MAPPINGS



#include "MilitaryMappings.h"
#include "ModLoader/ModLoader.h"
#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class allMilitaryMappings: commonItems::parser
{
  public:
	explicit allMilitaryMappings(std::istream& theStream);

	[[nodiscard]] const militaryMappings& getMilitaryMappings(const Mods& Vic2Mods) const;

  private:
	std::map<std::string, militaryMappings> theMappings;
};

} // namespace HoI4



#endif // ALL_MILITARY_MAPPINGS