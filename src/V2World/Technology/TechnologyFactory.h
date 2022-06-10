#ifndef TECHNOLOGY_FACTORY_H
#define TECHNOLOGY_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include <vector>



namespace Vic2
{

class TechnologyFactory: commonItems::parser
{
  public:
	TechnologyFactory();
	std::vector<std::string> importTechnologies(std::istream& theStream);

  private:
	std::vector<std::string> technologies;
};

} // namespace Vic2



#endif // TECHNOLOGY_FACTORY_H