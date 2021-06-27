#ifndef CASUS_BELLI_FACTORY_H
#define CASUS_BELLI_FACTORY_H



#include "CasusBelli.h"
#include "Parser.h"



namespace Mappers
{

class CasusBelliFactory: commonItems::parser
{
  public:
	CasusBelliFactory();
	CasusBelli importCasusBelli(std::istream& theStream);

  private:
	std::unordered_set<std::string> cbs_;
	std::string warGoal_;
};

} // namespace Mappers



#endif // CASUS_BELLI_FACTORY_H