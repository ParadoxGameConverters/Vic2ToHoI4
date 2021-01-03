#ifndef IDEA_UPDATERS_H
#define IDEA_UPDATERS_H



#include "IdeaGroup.h"
#include <set>
#include <string>



namespace HoI4
{

void updateMobilizationLaws(IdeaGroup& mobilizationLaws, const std::set<std::string>& majorIdeologies);
void updateEconomyIdeas(IdeaGroup& economicIdeas, const std::set<std::string>& majorIdeologies);
void updateTradeLaws(IdeaGroup& tradeLaws, const std::set<std::string>& majorIdeologies);
void updateGeneralIdeas(IdeaGroup& generalIdeas, const std::set<std::string>& majorIdeologies);
void updateNeutralIdeas(IdeaGroup& neutralIdeas, const std::set<std::string>& majorIdeologies);

} // namespace HoI4



#endif // IDEA_UPDATERS_H