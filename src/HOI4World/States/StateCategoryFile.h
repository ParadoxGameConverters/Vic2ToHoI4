#ifndef HOI4_STATE_CATEGORY_FILE_H
#define HOI4_STATE_CATEGORY_FILE_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/States/StateCategory.h"
#include <vector>



namespace HoI4
{

class StateCategoryFile: commonItems::parser
{
  public:
	explicit StateCategoryFile(std::istream& theStream);

	auto getCategories() const { return theCategories; }

  private:
	std::vector<StateCategory> theCategories;
};

} // namespace HoI4



#endif // HOI4_STATE_CATEGORY_FILE_H