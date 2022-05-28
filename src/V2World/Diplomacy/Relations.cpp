#include "Relations.h"



bool Vic2::Relations::operator==(const Relations& rhs) const
{
	return value == rhs.value && level == rhs.level && militaryAccess == rhs.militaryAccess &&
			 lastSentDiplomat.has_value() == rhs.lastSentDiplomat.has_value() &&
			 ((lastSentDiplomat.has_value() && lastSentDiplomat.value() == rhs.lastSentDiplomat.value()) ||
				  !lastSentDiplomat.has_value()) &&
			 lastWar.has_value() == rhs.lastWar.has_value() &&
			 ((lastWar.has_value() && lastWar.value() == rhs.lastWar.value()) || !lastWar.has_value()) &&
			 truceUntil.has_value() == rhs.truceUntil.has_value() &&
			 ((truceUntil.has_value() && truceUntil.value() == rhs.truceUntil.value()) || !truceUntil.has_value()) &&
			 influenceValue == rhs.influenceValue;
}