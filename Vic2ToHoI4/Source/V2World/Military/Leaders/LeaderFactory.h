#ifndef LEADER_FACTORY_H
#define LEADER_FACTORY_H



#include "Leader.h"
#include "Parser.h"
#include <memory>
#include "Traits.h"



namespace Vic2
{

class Leader::Factory: commonItems::parser
{
  public:
	Factory(Traits&& traits_);

	std::unique_ptr<Leader> getLeader(std::istream& theStream);

  private:
	Traits traits;
	std::unique_ptr<Leader> leader;
};

} // namespace Vic2



#endif // LEADER_FACTORY_H