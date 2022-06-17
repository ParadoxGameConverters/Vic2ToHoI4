#ifndef MOD_SPANISH_CIVIL_WAR_H
#define MOD_SPANISH_CIVIL_WAR_H

#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/ScenarioCreator/Roles/ScenarioMod.h"
#include "src/HOI4World/Decisions/DecisionsCategories.h"

class ModSpanishCivilWar: public ScenarioMod
{
  public:
	class Builder;
	ModSpanishCivilWar() = default;
	ModSpanishCivilWar(std::shared_ptr<HoI4::Country> country);

  private:
};

#endif // MOD_SPANISH_CIVIL_WAR_H