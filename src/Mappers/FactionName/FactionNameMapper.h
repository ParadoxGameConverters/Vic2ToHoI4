#ifndef FACTION_NAME_MAPPER_H
#define FACTION_NAME_MAPPER_H



#include "src/Mappers/FactionName/FactionNameMapping.h"
#include <optional>
#include <vector>



namespace Mappers
{

class FactionNameMapper
{
  public:
	class Factory;

	[[nodiscard]] std::optional<std::string> getFactionName(const std::string& HoI4Ideology,
		 const std::string& Hoi4Culture,
		 const std::string& Hoi4CultureGroup);

  private:
	std::vector<FactionNameMapping> mappings;
};

} // namespace Mappers



#endif // FACTION_NAME_MAPPER_H