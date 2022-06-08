#ifndef EXILED_GOVERNMENTS_DECISIONS
#define EXILED_GOVERNMENTS_DECISIONS



#include "src/HOI4World/Decisions/DecisionsFile.h"



namespace HoI4
{

class ExiledGovernmentsDecisions: public DecisionsFile
{
  public:
	void updateDecisions(const std::set<std::string>& majorIdeologies);
};

} // namespace HoI4



#endif // EXILED_GOVERNMENTS_DECISIONS