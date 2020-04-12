#ifndef PROVINCE_MAPPING_H
#define PROVINCE_MAPPING_H



#include "newParser.h"



namespace mappers
{

class ProvinceMapping: commonItems::parser
{
  public:
	explicit ProvinceMapping(std::istream& theStream);

	[[nodiscard]] auto getVic2Provinces() const { return Vic2Provinces; }
	[[nodiscard]] auto getHoI4Provinces() const { return HoI4Provinces; }

  private:
	std::vector<int> Vic2Provinces;
	std::vector<int> HoI4Provinces;
};

} // namespace mappers



#endif // PROVINCE_MAPPING_H