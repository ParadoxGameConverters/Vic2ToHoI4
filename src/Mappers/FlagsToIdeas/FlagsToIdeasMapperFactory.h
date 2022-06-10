#ifndef FLAGS_TO_IDEAS_MAPPER_FACTORY_H
#define FLAGS_TO_IDEAS_MAPPER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/FlagsToIdeas/FlagToIdeaMappingFactory.h"
#include "src/Mappers/FlagsToIdeas/FlagsToIdeasMapper.h"
#include <memory>



namespace Mappers
{

class FlagsToIdeasMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<FlagsToIdeasMapper> importFlagsToIdeaMapper();

  private:
	std::unique_ptr<FlagsToIdeasMapper> flagsToIdeaMapper;

	FlagToIdeaMapping::Factory factory;
};

} // namespace Mappers



#endif // FLAGS_TO_IDEAS_MAPPER_FACTORY_H