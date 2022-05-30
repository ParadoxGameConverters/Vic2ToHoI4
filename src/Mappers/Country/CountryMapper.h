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

  private:
	std::map<std::string, std::string> Vic2TagToHoI4TagMap;
};

} // namespace Mappers



#endif // COUNTRY_MAPPING_H