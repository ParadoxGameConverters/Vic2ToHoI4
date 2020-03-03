#ifndef HOI4_DIVISION_TEMPLATE_H
#define HOI4_DIVISION_TEMPLATE_H



#include "RegimentType.h"
#include "newParser.h"
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{


class DivisionTemplateType: commonItems::parser
{
  public:
	explicit DivisionTemplateType(std::istream& theStream);

	bool operator==(const std::string& rhs) const { return name == rhs; }

	friend std::ostream& operator<<(std::ostream& out, const DivisionTemplateType& rhs);

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getRegiments() const { return regiments; }
	[[nodiscard]] const auto& getSupportRegiments() const { return supportRegiments; }

  private:
	std::string name;
	std::vector<RegimentType> regiments;
	std::vector<RegimentType> supportRegiments;
};

} // namespace HoI4



#endif // HOI4_DIVISION_TEMPLATE_H
