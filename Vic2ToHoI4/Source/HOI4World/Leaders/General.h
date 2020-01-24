#ifndef GENERAL_H
#define GENERAL_H



#include "Commander.h"



namespace HoI4
{
	
class General: Commander
{
	public:
		General(const Vic2::Leader& srcLeader, const std::string& portrait);

		friend std::ostream& operator<<(std::ostream& output, const General& instance);

	private:
		int planningSkill = 1;
		int logisticsSkill = 1;
};
	
}




#endif // GENERAL_H