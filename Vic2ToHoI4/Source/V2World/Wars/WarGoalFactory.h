#ifndef WAR_GOAL_FACTORY_H_
#define WAR_GOAL_FACTORY_H_



#include "Parser.h"
#include "WarGoal.h"



namespace Vic2
{

class WarGoalFactory: commonItems::parser
{
  public:
	WarGoalFactory();

	WarGoal getWarGoal(std::istream& theStream);

  private:
	std::string casusBelli;
	std::optional<int> province;
};

} // namespace Vic2



#endif // WAR_GOAL_FACTORY_H_