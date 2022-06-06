#ifndef CASUS_BELLIS_FACTORY_H
#define CASUS_BELLIS_FACTORY_H



#include "CasusBelliMappingFactory.h"
#include "CasusBellis.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace Mappers
{

class CasusBellisFactory: commonItems::parser
{
  public:
	CasusBellisFactory();

	std::unique_ptr<CasusBellis> importCasusBellis();

  private:
	std::unordered_map<std::string, std::string> mappings;

	CasusBelliMappingFactory casusBelliFactory;
};

} // namespace Mappers



#endif // CASUS_BELLIS_FACTORY_H