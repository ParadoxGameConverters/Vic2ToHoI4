#ifndef PROVINCE_MAPPER_H
#define PROVINCE_MAPPER_H



#include "Configuration.h"
#include "Parser.h"
#include "ProvinceMappingTypes.h"
#include <map>
#include <optional>
#include <vector>



namespace Mappers
{

class ProvinceMapper
{
  public:
	class Parser;

	ProvinceMapper(HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap, Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap):
		 HoI4ToVic2ProvinceMap(std::move(HoI4ToVic2ProvinceMap)), Vic2ToHoI4ProvinceMap(std::move(Vic2ToHoI4ProvinceMap))
	{
	}

	[[nodiscard]] std::optional<std::vector<int>> getVic2ToHoI4ProvinceMapping(int Vic2Province) const;
	[[nodiscard]] std::optional<std::vector<int>> getHoI4ToVic2ProvinceMapping(int HoI4Province) const;

  private:
	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};


class ProvinceMapper::Parser: commonItems::parser
{
  public:
	ProvinceMapper initializeMapper(const Configuration& theConfiguration);

  private:
	void checkAllHoI4ProvincesMapped(const Configuration& theConfiguration) const;
	std::optional<int> getNextProvinceNumFromFile(std::ifstream& definitions) const;
	void verifyProvinceIsMapped(int provNum) const;

	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace mappers



#endif // PROVINCE_MAPPER_H