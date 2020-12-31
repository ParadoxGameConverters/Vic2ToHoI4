#ifndef ADMIRAL_H
#define ADMIRAL_H



#include "Commander.h"



namespace HoI4
{

class Admiral: Commander
{
  public:
	Admiral(const Vic2::Leader& srcLeader, const std::string& portrait);

	friend std::ostream& operator<<(std::ostream& output, const Admiral& admiral);

  private:
	int maneuveringSkill = 1;
	int coordinationSkill = 1;
};

} // namespace HoI4



#endif // ADMIRAL_H