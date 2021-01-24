#ifndef VERSIONED_MAPPINGS_H
#define VERSIONED_MAPPINGS_H



#include "ProvinceMappingTypes.h"
#include "Parser.h"



namespace Mappers
{

class VersionedMappings: commonItems::parser
{
  public:
	explicit VersionedMappings(std::istream& theStream);

	[[nodiscard]] auto getVic2ToHoI4Mapping() const { return Vic2ToHoI4ProvinceMap; }
	[[nodiscard]] auto getHoI4ToVic2Mapping() const { return HoI4ToVic2ProvinceMap; }

  private:
	void insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Provinces, const std::vector<int>& HoI4Provinces);
	void insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Provinces, const std::vector<int>& HoI4Provinces);

	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace mappers



#endif // VERSIONED_MAPPINGS_H