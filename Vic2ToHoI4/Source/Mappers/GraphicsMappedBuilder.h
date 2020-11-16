#ifndef GRAPHICS_MAPPER_BUILDER_H
#define GRAPHICS_MAPPER_BUILDER_H



#include "GraphicsMapper.h"
#include <memory>



class graphicsMapper::Builder
{
  public:
	Builder() { theGraphicsMapper = std::make_unique<graphicsMapper>(); }
	std::unique_ptr<graphicsMapper> Build() { return std::move(theGraphicsMapper); }

	Builder& addGraphicalCultureMapping(const std::string& cultureGroup, const std::string& graphicalCulture)
	{
		theGraphicsMapper->graphicalCultureMap.insert(std::make_pair(cultureGroup, graphicalCulture));
		return *this;
	}
	Builder& add2dGraphicalCultureMapping(const std::string& cultureGroup, const std::string& graphicalCulture2d)
	{
		theGraphicsMapper->graphicalCulture2dMap.insert(std::make_pair(cultureGroup, graphicalCulture2d));
		return *this;
	}

  private:
	std::unique_ptr<graphicsMapper> theGraphicsMapper;
};



#endif // GRAPHICS_MAPPER_BUILDER_H