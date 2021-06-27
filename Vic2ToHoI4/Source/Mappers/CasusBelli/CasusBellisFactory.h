#ifndef CASUS_BELLIS_FACTORY_H
#define CASUS_BELLIS_FACTORY_H



#include "CasusBellis.h"
#include <memory>


namespace Mappers
{

class CasusBellisFactory
{
  public:
	CasusBellisFactory();

	std::unique_ptr<CasusBellis> importCasusBellis();
};

} // namespace Mappers



#endif // CASUS_BELLIS_FACTORY_H