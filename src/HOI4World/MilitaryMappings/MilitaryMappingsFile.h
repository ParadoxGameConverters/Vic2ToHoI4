#ifndef MILITARY_MAPPINGS_FILE
#define MILITARY_MAPPINGS_FILE



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/MilitaryMappings/AllMilitaryMappings.h"
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