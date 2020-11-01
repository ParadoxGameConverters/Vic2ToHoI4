#ifndef COMMANDER_H
#define COMMANDER_H



#include "V2World/Military/Leaders/Leader.h"
#include <string>
#include <vector>



namespace HoI4
{

class Commander
{
  public:
	Commander(const Vic2::Leader& srcLeader, std::string portrait);

  protected:
	[[nodiscard]] int varySkill(int skill) const;

	std::string name;
	std::string picture;
	std::vector<std::string> traits;
	int skill = 1;
	int attackSkill = 1;
	int defenseSkill = 1;
};

} // namespace HoI4



#endif // COMMANDER_H