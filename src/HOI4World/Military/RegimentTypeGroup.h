#ifndef REGIMENT_TYPE_GROUP_H
#define REGIMENT_TYPE_GROUP_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Military/RegimentType.h"



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



#endif // REGIMENT_TYPE_GROUP_H