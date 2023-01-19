#ifndef PARTY_FACTORY_H
#define PARTY_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Politics/Party.h"
#include <memory>



namespace Vic2
{


class Party::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Party> getParty(std::istream& theStream);

  private:
	std::unique_ptr<Party> party;
};


} // namespace Vic2



#endif // PARTY_FACTORY_H