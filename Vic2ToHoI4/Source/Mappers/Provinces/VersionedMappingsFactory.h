#ifndef VERSIONED_MAPPINGS_FACTORY_H
#define VERSIONED_MAPPINGS_FACTORY_H



#include "Parser.h"
#include "ProvinceMapping.h"
#include "ProvinceMappingFactory.h"
#include "VersionedMappings.h"
#include <memory>



namespace Mappers
{

class VersionedMappings::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<VersionedMappings> importVersionedMappings(std::istream& theStream);

  private:
	void insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Provinces, const std::vector<int>& HoI4Provinces);
	void insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Provinces, const std::vector<int>& HoI4Provinces);

	ProvinceMapping::Factory provinceMappingFactory;

	std::unique_ptr<VersionedMappings> versionedMappings;
};

} // namespace Mappers



#endif // VERSIONED_MAPPINGS_FACTORY_H