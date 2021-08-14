#ifndef GRAPHICS_MAPPER_FACTORY_H
#define GRAPHICS_MAPPER_FACTORY_H



#include "GraphicsCultureGroupFactory.h"
#include "GraphicsMapper.h"
#include "Parser.h"



namespace Mappers
{

class GraphicsMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<GraphicsMapper> importGraphicsMapper();

  private:
	void loadMappings(const std::string& cultureGroupName, const GraphicsCultureGroup& graphicsCultureGroup);
	void loadLeaderPortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);
	void loadFemalePortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);
	void loadIdeologyMinisterPortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);

	GraphicsCultureGroup::Factory graphicsCultureGroupFactory;

	std::unique_ptr<GraphicsMapper> graphicsMapper;
};

} // namespace Mappers



#endif // GRAPHICS_MAPPER_FACTORY_H