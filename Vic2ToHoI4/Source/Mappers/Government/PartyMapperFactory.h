#ifndef PARTY_MAPPER_FACTORY_H
#define PARTY_MAPPER_FACTORY_H



#include "Parser.h"
#include "PartyMapper.h"
#include <memory>



namespace Mappers
{

class PartyMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<PartyMapper> importPartyMapper();

  private:
	std::unique_ptr<PartyMapper> partyMapper;
};

} // namespace Mappers



#endif // PARTY_MAPPER_FACTORY_H