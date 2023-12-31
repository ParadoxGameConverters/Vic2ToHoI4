#ifndef SCORERS_FACTORY_H
#define SCORERS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/Scorers/Scorers.h"


namespace HoI4
{

class Scorers::Factory: commonItems::parser
{
  public:
	std::unique_ptr<Scorers> getScorers();
};

} // namespace HoI4



#endif // SCORERS_FACTORY_H