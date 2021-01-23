#ifndef PROVINCE_MAPPING_H
#define PROVINCE_MAPPING_H



#include <vector>



namespace Mappers
{

class ProvinceMapping
{
  public:
	class Factory;

	[[nodiscard]] const auto& getVic2Provinces() const { return Vic2Provinces; }
	[[nodiscard]] const auto& getHoI4Provinces() const { return HoI4Provinces; }

  private:
	std::vector<int> Vic2Provinces;
	std::vector<int> HoI4Provinces;
};

} // namespace mappers



#endif // PROVINCE_MAPPING_H