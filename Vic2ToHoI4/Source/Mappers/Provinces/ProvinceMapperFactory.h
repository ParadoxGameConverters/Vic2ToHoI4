#ifndef PROVINCE_MAPPER_FACTORY_H
#define PROVINCE_MAPPER_FACTORY_H



#include "Configuration.h"
#include "Parser.h"
#include "ProvinceMapper.h"
#include "VersionedMappingsFactory.h"
#include <memory>



namespace Mappers
{

class ProvinceMapper::Factory: commonItems::parser
{
  public:
	Factory(const Configuration& theConfiguration);
	std::unique_ptr<ProvinceMapper> importProvinceMapper(const Configuration& theConfiguration);

  private:
	void checkAllHoI4ProvincesMapped(const Configuration& theConfiguration) const;
	std::optional<int> getNextProvinceNumFromFile(std::ifstream& definitions) const;
	void verifyProvinceIsMapped(int provNum) const;

	VersionedMappings::Factory versionedMappingsFactory;

	std::unique_ptr<ProvinceMapper> provinceMapper;
};

} // namespace Mappers



#endif // PROVINCE_MAPPER_FACTORY_H