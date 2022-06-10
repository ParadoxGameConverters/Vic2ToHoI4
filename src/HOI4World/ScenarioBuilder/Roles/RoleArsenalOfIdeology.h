#ifndef ROLE_ARSENAL_OF_IDEOLOGY_H
#define ROLE_ARSENAL_OF_IDEOLOGY_H

#include "Role.h"

class RoleArsenalOfIdeology: public Role
{
  public:
	bool isValid(const HoI4::Country& country) const;
	void calculateFit(const HoI4::Country& country);
	void apply(const std::shared_ptr<HoI4::Country> country_ptr);

  private:
};
#endif // ROLE_ARSENAL_OF_IDEOLOGY_H