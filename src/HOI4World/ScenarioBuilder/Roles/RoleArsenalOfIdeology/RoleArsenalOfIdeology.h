#ifndef ROLE_ARSENAL_OF_IDEOLOGY_H
#define ROLE_ARSENAL_OF_IDEOLOGY_H

#include "src/HOI4World/ScenarioBuilder/Roles/Role.h"

class RoleArsenalOfIdeology: public Role
{
  public:
	RoleArsenalOfIdeology();

	bool isValid(const HoI4::Country& country) const;
	void calculateFit(const HoI4::Country& country);
	std::shared_ptr<ScenarioMod> apply(const HoI4::Country& country);

  private:
};
#endif // ROLE_ARSENAL_OF_IDEOLOGY_H