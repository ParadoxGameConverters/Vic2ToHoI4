#ifndef OPERATIVE_NAMES_H
#define OPERATIVE_NAMES_H



#include "OperativeNamesSet.h"
#include <vector>



namespace HoI4
{

class OperativeNames
{
  public:
	class Factory;
	[[nodiscard]] const auto& getOperativeNamesSets() const { return operativeNamesSets; }

  private:
	std::vector<OperativeNamesSet> operativeNamesSets;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_H