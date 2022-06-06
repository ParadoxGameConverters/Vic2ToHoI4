#ifndef RELATIONS_FACTORY_H
#define RELATIONS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "Relations.h"
#include <memory>



namespace Vic2
{

class Relations::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Relations> getRelations(std::istream& theStream);

  private:
	std::unique_ptr<Relations> relations;
};

} // namespace Vic2



#endif // RELATIONS_FACTORY_H