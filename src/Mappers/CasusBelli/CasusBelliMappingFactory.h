#ifndef CASUS_BELLI_MAPPING_FACTORY_H
#define CASUS_BELLI_MAPPING_FACTORY_H



#include "CasusBelliMapping.h"
#include "Parser.h"



namespace Mappers
{

class CasusBelliMappingFactory: commonItems::parser
{
  public:
	CasusBelliMappingFactory();
	CasusBelliMapping importCasusBelli(std::istream& theStream);

  private:
	std::unordered_set<std::string> cbs_;
	std::string warGoal_;
};

} // namespace Mappers



#endif // CASUS_BELLI_MAPPING_FACTORY_H