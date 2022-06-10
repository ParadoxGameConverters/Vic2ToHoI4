#ifndef FOREIGN_INFLUENCE_DECISIONS
#define FOREIGN_INFLUENCE_DECISIONS



#include "src/HOI4World/Decisions/DecisionsFile.h"



namespace HoI4
{

class ForeignInfluenceDecisions: public DecisionsFile
{
  public:
	void updateDecisions(const std::set<std::string>& majorIdeologies);
};

} // namespace HoI4



#endif // FOREIGN_INFLUENCE_DECISIONS