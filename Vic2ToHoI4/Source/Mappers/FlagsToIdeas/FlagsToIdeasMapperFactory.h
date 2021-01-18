#ifndef FLAGS_TO_IDEAS_MAPPER_FACTORY_H
#define FLAGS_TO_IDEAS_MAPPER_FACTORY_H



#include "FlagToIdeaMappingFactory.h"
#include "FlagsToIdeasMapper.h"
#include "Parser.h"
#include <memory>



namespace Mappers
{

class FlagsToIdeasMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<FlagsToIdeasMapper> getFlagsToIdeaMapper(std::istream& theStream);

  private:
	std::unique_ptr<FlagsToIdeasMapper> flagsToIdeaMapper;

	FlagToIdeaMapping::Factory factory;
};

} // namespace Mappers



#endif // FLAGS_TO_IDEAS_MAPPER_FACTORY_H