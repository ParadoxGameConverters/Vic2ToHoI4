#ifndef PROVINCE_MAPPER_H
#define PROVINCE_MAPPER_H



#include "ProvinceMappingTypes.h"
#include <map>
#include <set>
#include <vector>



namespace Mappers
{

class ProvinceMapper
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] std::vector<int> getVic2ToHoI4ProvinceMapping(int Vic2Province) const;
	[[nodiscard]] std::vector<int> getHoI4ToVic2ProvinceMapping(int HoI4Province) const;
	[[nodiscard]] std::set<int> getEquivalentVic2Provinces(const std::set<int>& hoi4_provinces) const;

	[[nodiscard]] bool isVic2ProvinceMapped(int vic2ProvinceNum) const
	{
		return Vic2ToHoI4ProvinceMap.contains(vic2ProvinceNum);
	}

  private:
	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace Mappers



#endif // PROVINCE_MAPPER_H