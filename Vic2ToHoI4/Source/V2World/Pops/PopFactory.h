#ifndef POP_FACTORY_H
#define POP_FACTORY_H



#include "Parser.h"
#include "Pop.h"
#include "V2World/Issues/Issues.h"
#include <memory>



namespace Vic2
{

class Pop::Factory: commonItems::parser
{
  public:
	explicit Factory(Issues _theIssues);
	Pop getPop(const std::string& typeString, std::istream& theStream);

  private:
	PopOptions popOptions;
	const Issues theIssues;
};

} // namespace Vic2



#endif // POP_FACTORY_H