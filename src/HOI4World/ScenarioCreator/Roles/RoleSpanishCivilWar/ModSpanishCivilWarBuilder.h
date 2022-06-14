#ifndef MOD_SPANISH_CIVIL_WAR_BUILDER_H
#define MOD_SPANISH_CIVIL_WAR_BUILDER_H

#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"

class ModSpanishCivilWar::Builder
{
  public:
	Builder() { theCivilWarMod = std::make_unique<ModSpanishCivilWar>(); }
	std::unique_ptr<ModSpanishCivilWar> Build() { return std::move(theCivilWarMod); }

	Builder& addDecision(const std::string& file)
	{
		// stuff
	}

  private:
	std::unique_ptr<ModSpanishCivilWar> theCivilWarMod;

	static const std::string tag;
};

#endif // MOD_SPANISH_CIVIL_WAR_BUILDER_H