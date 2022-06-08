#ifndef OPERATIVE_NAMES_MAPPINGS_FACTORY_H
#define OPERATIVE_NAMES_MAPPINGS_FACTORY_H



#include "src/HOI4World/OperativeNames/OperativeNamesMappings.h"
#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class OperativeNamesMappings::Factory: commonItems::parser
{
  public:
	OperativeNamesMappings getMappings();
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_MAPPINGS_FACTORY_H