#include "CasusBellisFactory.h"



Mappers::CasusBellisFactory::CasusBellisFactory()
{
}


std::unique_ptr<Mappers::CasusBellis> Mappers::CasusBellisFactory::importCasusBellis()
{
	return std::make_unique<CasusBellis>();
}