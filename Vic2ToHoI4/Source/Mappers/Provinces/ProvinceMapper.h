#ifndef PROVINCE_MAPPER_H
#define PROVINCE_MAPPER_H



#include "ProvinceMappingTypes.h"
#include <map>
#include <optional>
#include <vector>



namespace Mappers
{

class ProvinceMapper
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] std::optional<std::vector<int>> getVic2ToHoI4ProvinceMapping(int Vic2Province) const;
	[[nodiscard]] std::optional<std::vector<int>> getHoI4ToVic2ProvinceMapping(int HoI4Province) const;

  private:
	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace Mappers



#endif // PROVINCE_MAPPER_H