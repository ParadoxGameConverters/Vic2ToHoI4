#ifndef IDEOLOGY_MAPPER_FACTORY_H
#define IDEOLOGY_MAPPER_FACTORY_H



#include "IdeologyMapper.h"
#include "IdeologyMappingFactory.h"
#include "Parser.h"
#include <memory>



namespace Mappers
{

class IdeologyMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<IdeologyMapper> importIdeologyMapper();

  private:
	IdeologyMappingFactory ideologyMappingFactory;

	std::unique_ptr<IdeologyMapper> ideologyMapper;
};

} // namespace Mappers



#endif // IDEOLOGY_MAPPER_FACTORY_H