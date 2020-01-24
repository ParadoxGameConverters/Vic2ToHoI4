#ifndef COMMANDER_H
#define COMMANDER_H



#include "../../V2World/Leader.h"
#include <string>
#include <vector>



namespace HoI4
{

class Commander
{
	public:
		Commander(const Vic2::Leader& srcLeader, const std::string& portrait);

	protected:
		int varySkill(int skill) const;
	
		std::string name;
		std::string picture;
		std::vector<std::string> traits;
		int skill = 1;
		int attackSkill = 1;
		int defenseSkill = 1;
};

}



#endif // COMMANDER_H