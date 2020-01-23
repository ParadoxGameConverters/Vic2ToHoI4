#ifndef ADMIRAL_H
#define ADMIRAL_H



#include "../../V2World/Leader.h"
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{
	
class Admiral
{
	public:
		Admiral(const Vic2::Leader& srcLeader, const std::string& portrait);

		friend std::ostream& operator<<(std::ostream& output, const Admiral& instance);

	private:
		std::string name;
		std::string picture;
		std::vector<std::string> traits;
		int skill = 1;
		int attackSkill = 1;
		int defenseSkill = 1;
		int maneuveringSkill = 1;
		int coordinationSkill = 1;
};
	
}



#endif // ADMIRAL_H