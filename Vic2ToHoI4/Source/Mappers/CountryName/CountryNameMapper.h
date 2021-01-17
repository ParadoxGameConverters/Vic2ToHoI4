#ifndef COUNTRY_NAME_MAPPER_H
#define COUNTRY_NAME_MAPPER_H



#include "CountryNameMapping.h"
#include <optional>
#include <vector>



namespace Mappers
{

class CountryNameMapper
{
  public:
	class Factory;

	[[nodiscard]] std::optional<std::string> getVic2Government(const std::string& HoI4Ideology,
		 const std::string& Vic2Tag) const;

  private:
	std::vector<CountryNameMapping> mappings;
};

} // namespace Mappers



#endif // COUNTRY_NAME_MAPPER_H