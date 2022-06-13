#ifndef ROLE_TEST_SHELL_H
#define ROLE_TEST_SHELL_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

class RoleTestShell: public Role
{
	// Class may not be usefull due to other testing contraints
  public:
	RoleTestShell() = default;

	bool isValid(const HoI4::Country& country) const;
	void calculateFit(const HoI4::Country& country);
	std::shared_ptr<ScenarioMod> apply(const HoI4::Country& country);

  private:
};
#endif // ROLE_TEST_SHELL_H