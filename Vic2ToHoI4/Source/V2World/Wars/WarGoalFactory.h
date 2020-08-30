#ifndef WAR_GOAL_FACTORY_H_
#define WAR_GOAL_FACTORY_H_



#include "Parser.h"



namespace Vic2
{

class WarGoalFactory: commonItems::parser
{
  public:
	WarGoalFactory();

	std::string getCB(std::istream& theStream);

  private:
	std::string CB;
};

} // namespace Vic2



#endif // WAR_GOAL_FACTORY_H_