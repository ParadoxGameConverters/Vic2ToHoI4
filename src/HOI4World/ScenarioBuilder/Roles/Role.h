#ifndef ROLE_H
#define ROLE_H

#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/ScenarioBuilder/Roles/ScenarioMod.h"

class Role
{
  public:
	Role() = default;

	[[nodiscard]] double getFit() const { return fit; };
	[[nodiscard]] std::string getName() const { return name; };

	// NOTE: const reference vs const ptr, any advantage/disadvantage between them?
	virtual bool isValid(const HoI4::Country& country) const = 0;
	virtual void calculateFit(const HoI4::Country& country) = 0;
	// NOTE: the ScenarioMod is optional, any good way to use a ptr and still mark it as such?
	// virtual std::optional<ScenarioMod> apply(const HoI4::Country& country) = 0;
	virtual std::shared_ptr<ScenarioMod> apply(const HoI4::Country& country) = 0;

	static bool roleComparator(const std::shared_ptr<Role> lhs, const std::shared_ptr<Role> rhs)
	{
		return lhs->getFit() < rhs->getFit();
	};

  protected:
	double fit = 1;					  // Score for how suited this role is for a given country
	unsigned short instances = 0;	  // # of times role is assigned
	unsigned short instanceCap = 0; // # of times role may be assigned

	std::string name = "";
};
#endif // ROLE_H