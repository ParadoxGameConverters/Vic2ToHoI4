#ifndef UNIT_FACTORY_H
#define UNIT_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Military/Unit.h"
#include <memory>



namespace Vic2
{

class Unit::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Unit> getUnit(std::istream& theStream);

  private:
	std::unique_ptr<Unit> unit;
};

} // namespace Vic2



#endif // UNIT_FACTORY_H