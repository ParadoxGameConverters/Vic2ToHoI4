#ifndef HOI4_STATE_CATEGORIES_H
#define HOI4_STATE_CATEGORIES_H



#include "src/Configuration.h"
#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>



namespace HoI4
{

class StateCategories: commonItems::parser
{
  public:
	StateCategories() = default;
	StateCategories(const Configuration& theConfiguration);
	~StateCategories() = default;

	class Builder;

	std::string getBestCategory(int numBuildingSlots) const;

  private:
	std::map<int, std::string> theCategories;
};

} // namespace HoI4



#endif // HOI4_STATE_CATEGORIES_H
