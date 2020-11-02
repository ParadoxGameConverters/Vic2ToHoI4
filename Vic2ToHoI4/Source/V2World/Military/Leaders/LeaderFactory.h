#ifndef LEADER_FACTORY_H
#define LEADER_FACTORY_H



#include "Leader.h"
#include "Parser.h"
#include "Traits.h"
#include <memory>



namespace Vic2
{

class Leader::Factory: commonItems::parser
{
  public:
	explicit Factory(Traits&& traits_);

	std::unique_ptr<Leader> getLeader(std::istream& theStream);

  private:
	Traits traits;
	std::unique_ptr<Leader> leader;
};

} // namespace Vic2



#endif // LEADER_FACTORY_H