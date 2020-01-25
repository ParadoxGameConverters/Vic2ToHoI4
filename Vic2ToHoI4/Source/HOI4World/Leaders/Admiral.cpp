#include "Admiral.h"



HoI4::Admiral::Admiral(const Vic2::Leader& srcLeader, const std::string& portrait):
	Commander(srcLeader, portrait)
{
	maneuveringSkill = varySkill(skill);
	coordinationSkill = varySkill(skill);
}