#ifndef HOI4_STATE_CATEGORIES_H
#define HOI4_STATE_CATEGORIES_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/States/StateCategory.h"
#include <string>
#include <vector>



namespace HoI4
{

class StateCategories: commonItems::parser
{
  public:
	StateCategories() = default;
	StateCategories(const Configuration& theConfiguration);
	~StateCategories() = default;

	class Builder;

	StateCategory getBestCategory(int numBuildingSlots, int navalBaseLevel) const;

  private:
	std::vector<StateCategory> theCategories;
};

} // namespace HoI4



#endif // HOI4_STATE_CATEGORIES_H
