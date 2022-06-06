#ifndef PROVINCE_MAPPING_FACTORY_H
#define PROVINCE_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "ProvinceMapping.h"
#include <memory>



namespace Mappers
{

class ProvinceMapping::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<ProvinceMapping> importProvinceMapping(std::istream& theStream);

  private:
	std::unique_ptr<ProvinceMapping> provinceMapping;
};

} // namespace Mappers



#endif // PROVINCE_MAPPING_FACTORY_H