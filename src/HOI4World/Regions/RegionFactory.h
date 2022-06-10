#ifndef REGION_FACTORY_H
#define REGION_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Regions/Region.h"
#include <memory>



namespace HoI4
{

class Region::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Region> importRegion(std::istream& theStream);

  private:
	std::unique_ptr<Region> region;
};

} // namespace HoI4



#endif // REGION_FACTORY_H