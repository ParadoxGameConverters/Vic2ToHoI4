#ifndef PROVINCE_MAPPER_BUILDER_H
#define PROVINCE_MAPPER_BUILDER_H



#include "ProvinceMapper.h"
#include <memory>



namespace Mappers
{

class ProvinceMapper::Builder
{
  public:
	Builder() { provinceMapper = std::make_unique<ProvinceMapper>(); }
	std::unique_ptr<ProvinceMapper> Build() { return std::move(provinceMapper); }

	Builder& addHoI4ToVic2ProvinceMapping(int HoI4Province, std::vector<int> Vic2Provinces)
	{
		provinceMapper->HoI4ToVic2ProvinceMap.insert(std::make_pair(HoI4Province, std::move(Vic2Provinces)));
		return *this;
	}

	Builder& addVic2ToHoI4ProvinceMap(int Vic2Province, std::vector<int> HoI4Provinces)
	{
		provinceMapper->Vic2ToHoI4ProvinceMap.insert(std::make_pair(Vic2Province, std::move(HoI4Provinces)));
		return *this;
	}

  private:
	std::unique_ptr<ProvinceMapper> provinceMapper;
};

} // namespace Mappers



#endif // PROVINCE_MAPPER_BUILDER_H