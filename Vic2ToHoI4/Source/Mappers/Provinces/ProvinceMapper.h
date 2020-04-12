#ifndef PROVINCE_MAPPER_H
#define PROVINCE_MAPPER_H



#include "ProvinceMappingTypes.h"
#include "newParser.h"
#include <map>
#include <optional>
#include <vector>



namespace mappers
{

class ProvinceMapper: commonItems::parser
{
  public:
	ProvinceMapper() = default;
	void initialize();
	void initialize(std::istream& input);
	virtual ~ProvinceMapper() = default;

	virtual std::optional<std::vector<int>> getVic2ToHoI4ProvinceMapping(int Vic2Province) const;
	std::optional<std::vector<int>> getHoI4ToVic2ProvinceMapping(int HoI4Province) const;

  private:
	ProvinceMapper(const ProvinceMapper&) = delete;
	ProvinceMapper& operator=(const ProvinceMapper&) = delete;

	void checkAllHoI4ProvinesMapped() const;
	std::optional<int> getNextProvinceNumFromFile(std::ifstream& definitions) const;
	void verifyProvinceIsMapped(int provNum) const;

	HoI4ToVic2ProvinceMapping HoI4ToVic2ProvinceMap;
	Vic2ToHoI4ProvinceMapping Vic2ToHoI4ProvinceMap;
};

} // namespace mappers



#endif // PROVINCE_MAPPER_H