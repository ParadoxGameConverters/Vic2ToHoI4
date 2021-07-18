#ifndef MILITARY_MAPPINGS_FILE
#define MILITARY_MAPPINGS_FILE



#include "AllMilitaryMappings.h"
#include "Parser.h"
#include <memory>



namespace HoI4
{

class militaryMappingsFile: commonItems::parser
{
  public:
	militaryMappingsFile();

	auto takeAllMilitaryMappings() { return std::move(theMilitaryMappings); }

  private:
	std::unique_ptr<allMilitaryMappings> theMilitaryMappings;
};

} // namespace HoI4



#endif // MILITARY_MAPPINGS_FILE