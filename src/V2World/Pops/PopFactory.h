#ifndef POP_FACTORY_H
#define POP_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Issues/Issues.h"
#include "src/V2World/Pops/Pop.h"
#include <memory>



namespace Vic2
{

class PopFactory: commonItems::parser
{
  public:
	explicit PopFactory(Issues _theIssues);
	Pop getPop(const std::string& typeString, std::istream& theStream);

  private:
	PopOptions popOptions;
	const Issues theIssues;
};

} // namespace Vic2



#endif // POP_FACTORY_H