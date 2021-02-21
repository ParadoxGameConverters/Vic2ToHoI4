#include "GovernmentMapperFactory.h"
#include "GovernmentMappingFactory.h"
#include "Log.h"



class governmentMappings: commonItems::parser
{
  public:
	explicit governmentMappings(std::istream& theStream);

	auto getGovernmentMap() const { return governmentMap; }

  private:
	Mappers::GovernmentMappingFactory governmentMappingFactory;
	std::vector<Mappers::GovernmentMapping> governmentMap;
};


governmentMappings::governmentMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		governmentMap.push_back(*governmentMappingFactory.importMapping(theStream));
	});

	parseStream(theStream);
}



Mappers::GovernmentMapper::Factory::Factory()
{
	registerKeyword("government_mappings", [this](std::istream& theStream) {
		governmentMappings mappings(theStream);
		governmentMapper->governmentMap = mappings.getGovernmentMap();
	});
}


std::unique_ptr<Mappers::GovernmentMapper> Mappers::GovernmentMapper::Factory::importGovernmentMapper()
{
	Log(LogLevel::Info) << "\tParsing governments mappings";

	governmentMapper = std::make_unique<GovernmentMapper>();
	parseFile("Configurables/governmentMapping.txt");
	return std::move(governmentMapper);
}