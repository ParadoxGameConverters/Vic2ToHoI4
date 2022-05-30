#ifndef OCCUPATION_LAWS_FACTORY_H
#define OCCUPATION_LAWS_FACTORY_H



#include "Configuration.h"
#include "OccupationLaws.h"
#include "Parser.h"


namespace HoI4
{

class OccupationLaws::Factory: commonItems::parser
{
  public:
	std::unique_ptr<OccupationLaws> getOccupationLaws(const Configuration& configuration);
};

} // namespace HoI4



#endif // OCCUPATION_LAWS_FACTORY_H