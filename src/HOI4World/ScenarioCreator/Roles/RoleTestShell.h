#ifndef ROLE_TEST_SHELL_H
#define ROLE_TEST_SHELL_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

class RoleTestShellOne: public Role
{
  public:
	RoleTestShellOne() = default;

	bool IsValid(const HoI4::Country& country) const override;
	bool IsPossible(const HoI4::Country& country) const override;
	void CalculateFit(const HoI4::Country& country) override;
	std::shared_ptr<ScenarioMod> Apply(std::shared_ptr<HoI4::Country> country) override;
};

class RoleTestShellTwo: public Role
{
  public:
	RoleTestShellTwo() = default;

	bool IsValid(const HoI4::Country& country) const override;
	bool IsPossible(const HoI4::Country& country) const override;
	void CalculateFit(const HoI4::Country& country) override;
	std::shared_ptr<ScenarioMod> Apply(std::shared_ptr<HoI4::Country> country) override;
};



#endif // ROLE_TEST_SHELL_H