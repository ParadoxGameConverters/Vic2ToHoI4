#include "PartyMapperFactory.h"
#include "PartyMappingFactory.h"



class partyMappings: commonItems::parser
{
  public:
	explicit partyMappings(std::istream& theStream);

	auto getPartyMap() const { return partyMap; }

  private:
	Mappers::PartyMappingFactory partyMappingFactory;
	std::vector<Mappers::PartyMapping> partyMap;
};


partyMappings::partyMappings(std::istream& theStream)
{
	registerKeyword("mapping", [this](std::istream& theStream) {
		partyMap.push_back(*partyMappingFactory.importPartyMapping(theStream));
	});

	parseStream(theStream);
}


Mappers::PartyMapper::Factory::Factory()
{
	registerKeyword("party_mappings", [this](std::istream& theStream) {
		partyMappings mappings(theStream);
		partyMapper->partyMap = mappings.getPartyMap();
	});
}


std::unique_ptr<Mappers::PartyMapper> Mappers::PartyMapper::Factory::importPartyMapper()
{
	partyMapper = std::make_unique<PartyMapper>();
	parseFile("Configurables/partyMapping.txt");
	return std::move(partyMapper);
}
