#ifndef ROLE_H
#define ROLE_H

#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/ScenarioCreator/Roles/ScenarioMod.h"

class Role
{
  public:
	Role() = default;

	[[nodiscard]] double GetFit() const { return fit_; };
	[[nodiscard]] std::string GetName() const { return name_; };

	virtual bool IsValid(const HoI4::Country& country) const = 0;
	virtual void CalculateFit(const HoI4::Country& country) = 0;
	virtual std::shared_ptr<ScenarioMod> Apply(std::shared_ptr<HoI4::Country> country) = 0;

	// True if greater fit, analagous to std::greater
	static bool RoleComparator(const std::shared_ptr<Role> lhs, const std::shared_ptr<Role> rhs)
	{
		return lhs->GetFit() > rhs->GetFit();
	};

	// When I ask myself why I did this later: https://google.github.io/styleguide/cppguide.html#Inheritance
	// (Delete comment once design is settled)
  protected:
	[[nodiscard]] int GetInstances() const { return instances_; };
	[[nodiscard]] int GetInstanceCap() const { return instance_cap_; };

	void SetFit(const double fit) { fit_ = fit; };
	void SetInstances(const int instances) { instances_ = instances; };
	void SetInstanceCap(const int instance_cap) { instance_cap_ = instance_cap; };
	void SetName(const std::string name) { name_ = name; };

  private:
	double fit_ = 1;		  // Score for how suited this role is for a given country
	int instances_ = 0;	  // # of times role is assigned
	int instance_cap_ = 0; // # of times role may be assigned

	std::string name_ = "";
};
#endif // ROLE_H