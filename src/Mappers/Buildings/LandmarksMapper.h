#ifndef LANDMARKS_MAPPER_H
#define LANDMARKS_MAPPER_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Buildings/LandmarksMapping.h"
#include <map>
#include <optional>



namespace Mappers
{

class LandmarksMapper: commonItems::parser
{
  public:
	LandmarksMapper();

	[[nodiscard]] const auto& getMappings() const { return mappings; }
	[[nodiscard]] std::optional<int> getLocation(const std::string& landmark) const;
	[[nodiscard]] bool getBuilt(const std::string& landmark) const;

  private:
	std::map<std::string, LandmarksMapping> mappings;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPER_H