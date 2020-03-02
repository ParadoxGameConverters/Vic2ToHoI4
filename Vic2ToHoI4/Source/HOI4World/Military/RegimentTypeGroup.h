#ifndef REGIMENT_TYPE_GROUP
#define REGIMENT_TYPE_GROUP



#include "RegimentType.h"
#include "newParser.h"



namespace HoI4
{

class RegimentTypeGroup: commonItems::parser
{
  public:
	explicit RegimentTypeGroup(std::istream& theStream);

	[[nodiscard]] auto&& takeRegimentTypes() const { return regimentTypes; }

  private:
	std::vector<RegimentType> regimentTypes;
};

} // namespace HoI4



#endif // REGIMENT_TYPE_GROUP