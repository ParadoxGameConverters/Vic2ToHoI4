#ifndef MOD_SPANISH_CIVIL_WAR_BUILDER_H
#define MOD_SPANISH_CIVIL_WAR_BUILDER_H

#include "external/common_items/Parser.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"

class ModSpanishCivilWar::Builder: commonItems::parser
{
  public:
	Builder() { theCivilWarMod = std::make_unique<ModSpanishCivilWar>(); }
	std::unique_ptr<ModSpanishCivilWar> Build() { return std::move(theCivilWarMod); }

	Builder& addDecision(const std::string& file, const std::string& category);
	Builder& addCategory(const std::string& file, const std::string& name);
	Builder& addEvent(const std::string& file, const std::string& category);

	void update(std::shared_ptr<ModSpanishCivilWar> a) { a->b = 2; }; // Does this work?

  private:
	std::unique_ptr<ModSpanishCivilWar> theCivilWarMod;

	static const std::string tag;
	static const std::string rebels;
};

#endif // MOD_SPANISH_CIVIL_WAR_BUILDER_H