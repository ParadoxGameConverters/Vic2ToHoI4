#ifndef GOVERNMENT_MAPPER_FACTORY
#define GOVERNMENT_MAPPER_FACTORY



#include "src/Mappers/Government/GovernmentMapper.h"
#include "src/Mappers/Government/GovernmentMappingFactory.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace Mappers
{

class GovernmentMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<GovernmentMapper> importGovernmentMapper();

  private:
	GovernmentMappingFactory governmentMappingFactory;

	std::unique_ptr<GovernmentMapper> governmentMapper;
};

} // namespace Mappers



#endif // GOVERNMENT_MAPPER_FACTORY