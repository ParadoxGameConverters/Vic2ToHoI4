#ifndef ALL_MILITARY_MAPPINGS
#define ALL_MILITARY_MAPPINGS



#include "MilitaryMappings.h"
#include "newParser.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class allMilitaryMappings: commonItems::parser
{
	public:
		explicit allMilitaryMappings(std::istream& theStream);

		[[nodiscard]] const militaryMappings& getMilitaryMappings(const std::vector<std::string>& Vic2Mods) const;

	private:
		std::map<std::string, militaryMappings> theMappings;
};

}



#endif // ALL_MILITARY_MAPPINGS