#ifndef VERSIONED_MAPPINGS_H
#define VERSIONED_MAPPINGS_H



#include "src/Mappers/Provinces/ProvinceMappingTypes.h"



namespace Mappers
{

class VersionedMappings
{
  public:
	class Factory;

	[[nodiscard]] auto& getVic2ToHoI4Mapping() const { return Vic2ToHoI4ProvinceMap; }
	[[nodiscard]] auto& getHoI4ToVic2Mapping() const { return HoI4ToVic2ProvinceMap; }

  private:
	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace Mappers



#endif // VERSIONED_MAPPINGS_H