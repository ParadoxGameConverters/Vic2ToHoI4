#ifndef DIPLOMACY_FACTORY_H
#define DIPLOMACY_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Diplomacy/AgreementFactory.h"
#include "src/V2World/Diplomacy/Diplomacy.h"
#include <memory>



namespace Vic2
{

class Diplomacy::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Diplomacy> getDiplomacy(std::istream& theStream);

  private:
	std::unique_ptr<Diplomacy> diplomacy;
	Agreement::Factory agreementFactory;
};

} // namespace Vic2



#endif // DIPLOMACY_FACTORY_H