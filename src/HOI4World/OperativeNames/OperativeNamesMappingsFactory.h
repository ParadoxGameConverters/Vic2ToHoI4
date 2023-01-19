#ifndef OPERATIVE_NAMES_MAPPINGS_FACTORY_H
#define OPERATIVE_NAMES_MAPPINGS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/OperativeNames/OperativeNamesMappings.h"



namespace HoI4
{

class OperativeNamesMappings::Factory: commonItems::parser
{
  public:
	OperativeNamesMappings getMappings();
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_MAPPINGS_FACTORY_H