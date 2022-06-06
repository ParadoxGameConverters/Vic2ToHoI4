#ifndef HOI4_REGIMENT_TYPE_H
#define HOI4_REGIMENT_TYPE_H



#include "external/common_items/ConvenientParser.h"
#include <ostream>
#include <string>



namespace HoI4
{

class RegimentType: commonItems::parser
{
  public:
	explicit RegimentType(const std::string& _type, std::istream& theStream);

	[[nodiscard]] const std::string& getType() const { return type; }

	friend std::ostream& operator<<(std::ostream& out, const RegimentType& regiment);

  private:
	std::string type;
	int x = 0;
	int y = 0;
};

} // namespace HoI4



#endif // HOI4_REGIMENT_TYPE_H