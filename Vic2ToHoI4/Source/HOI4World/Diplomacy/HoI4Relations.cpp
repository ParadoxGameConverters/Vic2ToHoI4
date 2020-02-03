#include "HoI4Relations.h"
#include "../../V2World/Relations.h"



HoI4Relations::HoI4Relations(const std::string& newTag):
	tag(newTag),
	value(0),
	militaryAccess(false),
	lastSendDiplomat(date()),
	lastWar(date()),
	truceUntil(date()),
	influenceValue(0),
	guarantee(false),
	sphereLeader(false)
{
}


HoI4Relations::HoI4Relations(const std::string& newTag, const Vic2::Relations* oldRelations):
	tag(newTag),
	value(oldRelations->getRelations()),
	militaryAccess(oldRelations->hasMilitaryAccess()),
	lastSendDiplomat(oldRelations->getDiplomatLastSent()),
	lastWar(oldRelations->getLastWar()),
	truceUntil(oldRelations->getTruceUntil()),
	influenceValue(oldRelations->getInfluenceValue()),
	guarantee(oldRelations->getLevel() >= 4),
	sphereLeader(oldRelations->getLevel() >= 5)
{}
