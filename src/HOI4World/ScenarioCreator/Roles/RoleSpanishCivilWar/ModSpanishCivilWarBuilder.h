#ifndef MOD_SPANISH_CIVIL_WAR_BUILDER_H
#define MOD_SPANISH_CIVIL_WAR_BUILDER_H

#include "external/common_items/Parser.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"

class ModSpanishCivilWar::Builder: commonItems::parser
{
  public:
	Builder() { the_civil_war_mod_ = std::make_unique<ModSpanishCivilWar>(); }
	std::unique_ptr<ModSpanishCivilWar> Build() { return std::move(the_civil_war_mod_); }

	Builder& AddDecision(const std::string& file, const std::string& category);
	Builder& AddCategory(const std::string& file, const std::string& name);
	Builder& AddEvent(const std::string& file, const std::string& category);

	void update(std::shared_ptr<ModSpanishCivilWar> a) { a->b = 2; }; // Does this work?

  private:
	std::unique_ptr<ModSpanishCivilWar> the_civil_war_mod_;

	static const std::string kTag;
	static const std::string kCapitalState;
	static const std::string kPlotterIdeology;
	static const std::string kGovernmentIdeology;
};

#endif // MOD_SPANISH_CIVIL_WAR_BUILDER_H