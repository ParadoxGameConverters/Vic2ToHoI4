#ifndef AGENT_RECRUITMENT_DECISIONS_H
#define AGENT_RECRUITMENT_DECISIONS_H



#include "DecisionsFile.h"



namespace HoI4
{

class AgentRecruitmentDecisions: public DecisionsFile
{
  public:
	void updateDecisions(const std::set<std::string>& southAsianCountries);
};

} // namespace HoI4



#endif // AGENT_RECRUITMENT_DECISIONS_H