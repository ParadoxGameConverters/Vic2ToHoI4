#ifndef GENERAL_H
#define GENERAL_H



#include "Commander.h"



namespace HoI4
{

class General: Commander
{
  public:
	General(const Vic2::Leader& srcLeader);

	friend std::ostream& operator<<(std::ostream& output, const General& general);

  private:
	int planningSkill = 1;
	int logisticsSkill = 1;
};

} // namespace HoI4



#endif // GENERAL_H