#ifndef ROLE_TEST_SHELL_H
#define ROLE_TEST_SHELL_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

class RoleTestShellOne: public Role
{
  public:
	RoleTestShellOne() = default;

	bool isValid(const HoI4::Country& country) const;
	void calculateFit(const HoI4::Country& country);
	std::shared_ptr<ScenarioMod> apply(std::shared_ptr<HoI4::Country> country);

  private:
};

class RoleTestShellTwo: public Role
{
  public:
	RoleTestShellTwo() = default;

	bool isValid(const HoI4::Country& country) const;
	void calculateFit(const HoI4::Country& country);
	std::shared_ptr<ScenarioMod> apply(std::shared_ptr<HoI4::Country> country);

  private:
};



#endif // ROLE_TEST_SHELL_H