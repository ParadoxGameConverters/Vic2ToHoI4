#ifndef FLAG_TO_IDEA_MAPPING_FACTORY_H
#define FLAG_TO_IDEA_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/FlagsToIdeas/FlagToIdeaMapping.h"
#include <memory>



namespace Mappers
{

class FlagToIdeaMapping::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<FlagToIdeaMapping> importFlagToIdeaMapping(std::istream& theStream);

  private:
	std::unique_ptr<FlagToIdeaMapping> flagToIdeaMapping;
};

} // namespace Mappers



#endif // FLAG_TO_IDEA_MAPPING_FACTORY_H