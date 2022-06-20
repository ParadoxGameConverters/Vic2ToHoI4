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

	void OutputRoleSpecifics(std::string output_name) const override;

  private:
	void OutputExtraOnActions(std::string output_name) const;

	std::string election_on_action_event_;
};

#endif // MOD_SPANISH_CIVIL_WAR_H