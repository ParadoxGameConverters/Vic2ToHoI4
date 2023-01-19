#ifndef COASTAL_PROVINCES_BUILDER_H
#define COASTAL_PROVINCES_BUILDER_H



#include "src/HOI4World/Map/CoastalProvinces.h"
#include <memory>



namespace HoI4
{


class CoastalProvinces::Builder
{
  public:
	Builder() { coastalProvinces = std::make_unique<CoastalProvinces>(); }
	std::unique_ptr<CoastalProvinces> Build() { return std::move(coastalProvinces); }

	Builder& addCoastalProvince(int province, const std::vector<int>& connectingSeaProvince)
	{
		coastalProvinces->theCoastalProvinces[province] = connectingSeaProvince;
		return *this;
	}

  private:
	std::unique_ptr<CoastalProvinces> coastalProvinces;
};



} // namespace HoI4



#endif // COASTAL_PROVINCES_BUILDER_H