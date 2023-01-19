#ifndef OPERATIONS_FACTORY_H
#define OPERATIONS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Operations/Operations.h"
#include <memory>
#include <string>



namespace HoI4
{

class Operations::Factory: commonItems::parser
{
  public:
	std::unique_ptr<Operations> getOperations();
};

} // namespace HoI4



#endif // OPERATIONS_FACTORY_H