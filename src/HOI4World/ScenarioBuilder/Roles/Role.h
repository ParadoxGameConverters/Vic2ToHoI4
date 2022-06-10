#ifndef ROLE_H
#define ROLE_H

#include "src/HOI4World/HoI4Country.h"

class Role
{
  public:
	Role(): fit(1), instances(0){};

	[[nodiscard]] double getFit() const { return fit; };

	virtual bool isValid(const HoI4::Country& country) const = 0;
	virtual void calculateFit(const HoI4::Country& country) = 0;
	virtual void apply(const std::shared_ptr<HoI4::Country> country_ptr) = 0;

	static bool roleComparator(const Role* lhs, const Role* rhs) { return lhs->getFit() < rhs->getFit(); };

  private:
	double fit;
	int instances;
};
#endif // ROLE