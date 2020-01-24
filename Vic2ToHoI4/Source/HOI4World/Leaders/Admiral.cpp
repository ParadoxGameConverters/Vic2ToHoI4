#include "Admiral.h"
#include "OSCompatibilityLayer.h"



HoI4::Admiral::Admiral(const Vic2::Leader& srcLeader, const std::string& portrait):
	Commander(srcLeader, portrait)
{
	maneuveringSkill = skill;
	coordinationSkill = skill;
}