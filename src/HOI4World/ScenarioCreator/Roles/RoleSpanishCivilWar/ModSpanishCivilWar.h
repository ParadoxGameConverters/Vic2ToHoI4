#ifndef MOD_SPANISH_CIVIL_WAR_H
#define MOD_SPANISH_CIVIL_WAR_H

#include "src/HOI4World/Decisions/DecisionsCategories.h"
#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/ScenarioCreator/Roles/ScenarioMod.h"

class ModSpanishCivilWar: public ScenarioMod
{
  public:
	class Builder;
	ModSpanishCivilWar() = default;
	ModSpanishCivilWar(std::shared_ptr<HoI4::Country> country);

	// Could put this in the builder, store builders and only build at last second, shake up inheritence a bit.
	// Keep functions tight in scope in builder, some effectively static and these add functions can reuse that code.
	// void AddDecision(const std::string& file, const std::string& category);

  private:
};

#endif // MOD_SPANISH_CIVIL_WAR_H