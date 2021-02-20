#include "IdeologyMapperFactory.h"
#include "IdeologyMappingFactory.h"



class IdeologyMappings: commonItems::parser
{
  public:
	explicit IdeologyMappings(std::istream& theStream);

	auto getIdeologyMap() const { return ideologyMap; }

  private:
	Mappers::IdeologyMappingFactory ideologyMappingFactory;
	std::vector<Mappers::IdeologyMapping> ideologyMap;
};


IdeologyMappings::IdeologyMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		ideologyMap.push_back(*ideologyMappingFactory.importIdeologyMapping(theStream));
	});

	parseStream(theStream);
}


Mappers::IdeologyMapper::Factory::Factory()
{
	registerKeyword("ideology_mappings", [this](std::istream& theStream) {
		IdeologyMappings mappings(theStream);
		ideologyMapper->ideologyMap = mappings.getIdeologyMap();
	});
}


std::unique_ptr<Mappers::IdeologyMapper> Mappers::IdeologyMapper::Factory::importIdeologyMapper()
{
	ideologyMapper = std::make_unique<IdeologyMapper>();
	parseFile("Configurables/IdeologyMappings.txt");
	return std::move(ideologyMapper);
}
