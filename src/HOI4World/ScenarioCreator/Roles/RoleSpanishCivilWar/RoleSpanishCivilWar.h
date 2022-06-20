#ifndef ROLE_SPANISH_CIVIL_WAR_H
#define ROLE_SPANISH_CIVIL_WAR_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

class RoleSpanishCivilWar: public Role
{
  public:
	RoleSpanishCivilWar();
	RoleSpanishCivilWar(const date& the_date);

	bool IsValid(const HoI4::Country& country) const override;
	void CalculateFit(const HoI4::Country& country) override;
	std::shared_ptr<ScenarioMod> Apply(std::shared_ptr<HoI4::Country> country) override;

  private:
	const date the_date_;
};
#endif // ROLE_SPANISH_CIVIL_WAR_H