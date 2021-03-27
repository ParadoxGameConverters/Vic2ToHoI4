#ifndef GRAPHICS_CULTURE_GROUP_FACTORY_H
#define GRAPHICS_CULTURE_GROUP_FACTORY_H



#include "GraphicsCultureGroup.h"
#include "IdeologyToPortraitsMappingFactory.h"
#include "Parser.h"
#include <memory>



namespace Mappers
{

class GraphicsCultureGroup::Factory: commonItems::parser
{
  public:
	Factory();

	std::unique_ptr<GraphicsCultureGroup> importCultureGroup(std::istream& theStream);

  private:
	IdeologyToPortraitsMappingFactory ideologyToPortraitsMappingFactory;

	std::unique_ptr<GraphicsCultureGroup> graphicsCultureGroup;
};

} // namespace Mappers



#endif // GRAPHICS_CULTURE_GROUP_FACTORY_H