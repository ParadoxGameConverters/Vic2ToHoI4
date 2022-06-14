#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"

ModSpanishCivilWar::ModSpanishCivilWar(std::shared_ptr<HoI4::Country> country)
{
	name = country->getTag() + "_SpanishCivilWar";
}
