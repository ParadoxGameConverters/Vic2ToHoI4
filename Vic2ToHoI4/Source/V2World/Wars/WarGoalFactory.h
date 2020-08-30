#ifndef WARGOAL_H_
#define WARGOAL_H_



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



#endif // WARGOAL_H_