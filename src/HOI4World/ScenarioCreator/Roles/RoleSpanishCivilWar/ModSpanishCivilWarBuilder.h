#ifndef MOD_SPANISH_CIVIL_WAR_BUILDER_H
#define MOD_SPANISH_CIVIL_WAR_BUILDER_H

#include "external/common_items/Parser.h"
#include "src/HOI4World/ScenarioCreator/Roles/RoleSpanishCivilWar/ModSpanishCivilWar.h"

class ModSpanishCivilWar::Builder: commonItems::parser
{
  public:
	Builder();
	std::unique_ptr<ModSpanishCivilWar> Build() { return std::move(the_civil_war_mod_); }

	Builder& AddDecision(const std::string& file, const std::string& category);
	Builder& AddCategory(const std::string& file, const std::string& name);
	Builder& AddEvent(const std::string& file, const std::string& category);

  private:
	static const std::string kFolder;
	static const std::string kTag;
	static const std::string kCapitalState;
	static const std::string kState;
	static const std::string kPlotterIdeology;
	static const std::string kGovernmentIdeology;

	std::unique_ptr<ModSpanishCivilWar> the_civil_war_mod_;
};

#endif // MOD_SPANISH_CIVIL_WAR_BUILDER_H