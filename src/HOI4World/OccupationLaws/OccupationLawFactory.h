#ifndef OCCUPATION_LAW_FACTORY_H
#define OCCUPATION_LAW_FACTORY_H



#include "OccupationLaw.h"
#include "Parser.h"
#include <memory>



namespace HoI4
{

class OccupationLaw::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<OccupationLaw> getOccupationLaw(const std::string& name, std::istream& theStream);

  private:
	std::unique_ptr<OccupationLaw> occupationLaw;
};

} // namespace HoI4



#endif // OCCUPATION_LAW_FACTORY_H