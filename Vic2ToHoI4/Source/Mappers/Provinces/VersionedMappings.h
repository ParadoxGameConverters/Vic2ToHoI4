#include "ProvinceMappingTypes.h"
#include "newParser.h"



namespace mappers
{

class VersionedMappings: commonItems::parser
{
  public:
	VersionedMappings(std::istream& theStream);

	auto getVic2ToHoI4Mapping() const { return Vic2ToHoI4ProvinceMap; }
	auto getHoI4ToVic2Mapping() const { return HoI4ToVic2ProvinceMap; }

  private:
	void insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Nums, const std::vector<int>& HoI4nums);
	void insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Nums, const std::vector<int>& HoI4nums);

	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace mappers