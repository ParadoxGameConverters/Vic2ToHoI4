#ifndef ARMY_FACTORY_H
#define ARMY_FACTORY_H



#include "src/V2World/Military/Army.h"
#include "src/V2World/Military/UnitFactory.h"
#include "external/common_items/ConvenientParser.h"
#include <memory>



namespace Vic2
{

class Army::Factory: commonItems::parser
{
  public:
	Factory();

	std::unique_ptr<Army> getArmy(std::string owner, std::istream& theStream);

  private:
	std::unique_ptr<Army> army;
	Unit::Factory unitFactory;
};

} // namespace Vic2



#endif // ARMY_FACTORY_H