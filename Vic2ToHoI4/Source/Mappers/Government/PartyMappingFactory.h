#ifndef PARTY_MAPPING_FACTORY_H
#define PARTY_MAPPING_FACTORY_H



#include "ConvenientParser.h"
#include "PartyMapping.h"
#include <memory>



namespace Mappers
{

class PartyMappingFactory: commonItems::convenientParser
{
  public:
	PartyMappingFactory();
	std::unique_ptr<PartyMapping> importPartyMapping(std::istream& theStream);

  private:
	std::unique_ptr<PartyMapping> partyMapping;
};

} // namespace Mappers



#endif // PARTY_MAPPING_FACTORY_H