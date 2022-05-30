#ifndef OCCUPATION_LAWS_H
#define OCCUPATION_LAWS_H



#include "OccupationLaw.h"
#include <set>
#include <vector>



namespace HoI4
{

class OccupationLaws
{
  public:
	class Factory;
	[[nodiscard]] const auto& getOccupationLaws() const { return occupationLaws; }

	void giveOccupationLaw(OccupationLaw&& occupationLaw) { occupationLaws.emplace_back(occupationLaw); }

	void updateLaws(const std::set<std::string>& majorIdeologies);

  private:
	std::vector<OccupationLaw> occupationLaws;
};

} // namespace HoI4



#endif // OCCUPATION_LAWS_H