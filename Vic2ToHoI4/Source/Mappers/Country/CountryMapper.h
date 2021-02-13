#ifndef COUNTRY_MAPPING_H
#define COUNTRY_MAPPING_H



#include "Parser.h"
#include <map>
#include <optional>
#include <string>



namespace Mappers
{

class CountryMapper
{
  public:
	class Builder;
	class Factory;

	[[nodiscard]] std::optional<std::string> getHoI4Tag(const std::string& V2Tag) const;
	[[nodiscard]] std::optional<std::string> getVic2Tag(const std::string& HoI4Tag) const;

  private:
	std::map<std::string, std::string> Vic2TagToHoI4TagsRules;
	std::map<std::string, std::string> V2TagToHoI4TagMap;
	std::map<std::string, std::string> HoI4TagToV2TagMap;
};

} // namespace Mappers



#endif // COUNTRY_MAPPING_H