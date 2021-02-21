#ifndef GOVERNMENT_MAPPER_FACTORY
#define GOVERNMENT_MAPPER_FACTORY



#include "GovernmentMapper.h"
#include "Parser.h"
#include <memory>



namespace Mappers
{

class GovernmentMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<GovernmentMapper> importGovernmentMapper();

  private:
	std::unique_ptr<GovernmentMapper> governmentMapper;
};

} // namespace Mappers



#endif // GOVERNMENT_MAPPER_FACTORY