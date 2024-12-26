#ifndef LANDMARKS_MAPPER_H
#define LANDMARKS_MAPPER_H



#include "src/Mappers/Buildings/LandmarksMapping.h"
#include <optional>
#include <vector>



namespace Mappers
{

class LandmarksMapper
{
  public:
	class Factory;

	[[nodiscard]] const auto& getMappings() const { return mappings; }

  private:
	std::vector<LandmarksMapping> mappings;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPER_H