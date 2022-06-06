#ifndef AGREEMENT_FACTORY_H
#define AGREEMENT_FACTORY_H



#include "Agreement.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace Vic2
{

class Agreement::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Agreement> getAgreement(const std::string& agreementType, std::istream& theStream);

  private:
	std::unique_ptr<Agreement> agreement;
};

} // namespace Vic2



#endif // AGREEMENT_FACTORY_H