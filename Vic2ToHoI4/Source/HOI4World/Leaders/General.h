#ifndef GENERAL_H
#define GENERAL_H



#include "../../V2World/Leader.h"
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{
	
class General
{
	public:
		General(const Vic2::Leader* srcLeader, const std::string& portrait);
		General(const General&) = default;

		friend std::ostream& operator<<(std::ostream& output, const General& instance);

	private:
		General& operator=(const General&) = delete;

		std::string name;
		std::string picture;
		std::vector<std::string> traits;
		int skill = 1;
		int attackSkill = 1;
		int defenseSkill = 1;
		int planningSkill = 1;
		int logisticsSkill = 1;
};
	
}




#endif // GENERAL_H