#ifndef ROLE_ARSENAL_OF_IDEOLOGY_H
#define ROLE_ARSENAL_OF_IDEOLOGY_H

#include "src/HOI4World/ScenarioCreator/Roles/Role.h"

class RoleArsenalOfIdeology: public Role
{
  public:
	RoleArsenalOfIdeology();

	bool IsValid(const HoI4::Country& country) const override;
	bool IsPossible(const HoI4::Country& country) const override;
	void CalculateFit(const HoI4::Country& country) override;
	std::shared_ptr<ScenarioMod> Apply(std::shared_ptr<HoI4::Country> country) override;

  private:
};
#endif // ROLE_ARSENAL_OF_IDEOLOGY_H