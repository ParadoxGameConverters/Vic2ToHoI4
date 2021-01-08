#ifndef TECH_MAPPER_H
#define TECH_MAPPER_H



#include "TechMapping.h"
#include <vector>



namespace Mappers
{

class TechMapper
{
  public:
	class Factory;

	[[nodiscard]] auto getTechMappings() const { return techMappings; }

  private:
	std::vector<TechMapping> techMappings;
};

} // namespace Mappers



#endif // TECH_MAPPER_H