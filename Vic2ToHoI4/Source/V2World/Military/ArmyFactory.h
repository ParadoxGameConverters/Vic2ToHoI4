#ifndef ARMY_FACTORY_H
#define ARMY_FACTORY_H



#include "Army.h"
#include "Parser.h"
#include "UnitFactory.h"
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