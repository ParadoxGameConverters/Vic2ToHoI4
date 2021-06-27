#include "CasusBellisFactory.h"



Mappers::CasusBellisFactory::CasusBellisFactory()
{
}


std::unique_ptr<Mappers::CasusBellis> Mappers::CasusBellisFactory::importCasusBellis()
{
	return std::make_unique<CasusBellis>(
		 std::unordered_map<std::string, std::string>{{"demand_concession_casus_belli", "take_state"}});
}