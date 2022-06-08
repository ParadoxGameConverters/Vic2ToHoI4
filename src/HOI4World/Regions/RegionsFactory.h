#ifndef HOI4_REGIONS_FACTORY_H
#define HOI4_REGIONS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Regions/RegionFactory.h"
#include "src/HOI4World/Regions/Regions.h"
#include <memory>



namespace HoI4
{

class Regions::Factory: commonItems::parser
{
  public:
	Factory();

	std::unique_ptr<Regions> getRegions();

  private:
	Region::Factory regionFactory;

	std::unique_ptr<Regions> theRegions;
};

} // namespace HoI4



#endif // HOI4_REGIONS_FACTORY_H