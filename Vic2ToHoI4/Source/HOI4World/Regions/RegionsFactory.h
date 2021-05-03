#ifndef HOI4_REGIONS_FACTORY_H
#define HOI4_REGIONS_FACTORY_H



#include "Parser.h"
#include "Regions.h"
#include "RegionFactory.h"
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