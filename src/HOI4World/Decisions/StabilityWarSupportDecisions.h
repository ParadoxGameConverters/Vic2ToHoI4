#ifndef STABILITY_WAR_SUPPORT_DECISIONS_H
#define STABILITY_WAR_SUPPORT_DECISIONS_H



#include "src/HOI4World/Decisions/DecisionsFile.h"
#include <set>
#include <string>



namespace HoI4
{

class StabilityWarSupportDecisions: public DecisionsFile
{
  public:
	void updateDecisions(const std::set<std::string>& majorIdeologies);
};

} // namespace HoI4


#endif // STABILITY_WAR_SUPPORT_DECISIONS_H