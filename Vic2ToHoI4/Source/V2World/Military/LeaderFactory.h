#ifndef LEADER_FACTORY_H
#define LEADER_FACTORY_H



#include "Leader.h"
#include "Parser.h"
#include <memory>



namespace Vic2
{

class Leader::Factory: commonItems::parser
{
  public:
	Factory();

	std::unique_ptr<Leader> getLeader(std::istream& theStream);

  private:
	std::unique_ptr<Leader> leader;
};

} // namespace Vic2



#endif // LEADER_FACTORY_H