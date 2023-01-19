#ifndef OCCUPATION_LAWS_FACTORY_H
#define OCCUPATION_LAWS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/OccupationLaws/OccupationLaws.h"


namespace HoI4
{

class OccupationLaws::Factory: commonItems::parser
{
  public:
	std::unique_ptr<OccupationLaws> getOccupationLaws();
};

} // namespace HoI4



#endif // OCCUPATION_LAWS_FACTORY_H