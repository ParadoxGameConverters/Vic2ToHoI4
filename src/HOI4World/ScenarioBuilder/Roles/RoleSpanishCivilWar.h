#ifndef ROLE_SPANISH_CIVIL_WAR_H
#define ROLE_SPANISH_CIVIL_WAR_H

#include "Role.h"

class RoleSpanishCivilWar: Role
{
  public:
	bool isValid(const HoI4::Country& country) const;
	void calculateFit(const HoI4::Country& country);
	void apply(const std::shared_ptr<HoI4::Country> country_ptr);

  private:
};
#endif // ROLE_SPANISH_CIVIL_WAR_H