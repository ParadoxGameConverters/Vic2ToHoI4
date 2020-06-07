#ifndef POP_FACTORY_H
#define POP_FACTORY_H



#include "../Issues/Issues.h"
#include "Parser.h"
#include "Pop.h"
#include <memory>



namespace Vic2
{
class Pop::Factory: commonItems::parser
{
  public:
	explicit Factory(const Issues& theIssues);
	std::unique_ptr<Pop> getPop(const std::string& typeString, std::istream& theStream);

  private:
	std::unique_ptr<Pop> pop;
	const Issues theIssues;
};
} // namespace Vic2



#endif // POP_FACTORY_H