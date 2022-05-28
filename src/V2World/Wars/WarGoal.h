#ifndef WAR_GOAL_H
#define WAR_GOAL_H



#include <optional>
#include <string>



namespace Vic2
{

struct WarGoal
{
	std::string casusBelli;
	std::optional<int> province;
};

} // namespace Vic2



#endif // WAR_GOAL_H