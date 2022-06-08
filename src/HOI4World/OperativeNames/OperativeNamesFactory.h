#ifndef OPERATIVE_NAMES_FACTORY_H
#define OPERATIVE_NAMES_FACTORY_H



#include "src/HOI4World/OperativeNames/OperativeNames.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace HoI4
{

class OperativeNames::Factory: commonItems::parser
{
  public:
	static std::unique_ptr<OperativeNames> getOperativeNames(const std::string& HoI4Path);
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_FACTORY_H