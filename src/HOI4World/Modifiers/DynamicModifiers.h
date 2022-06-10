#ifndef HOI4_DYNAMIC_MODIFIERS_H
#define HOI4_DYNAMIC_MODIFIERS_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Modifiers/Modifier.h"
#include <set>



namespace HoI4
{

class DynamicModifiers: commonItems::parser
{
  public:
	DynamicModifiers();

	[[nodiscard]] const auto& getDynamicModifiers() const { return dynamicModifiers; }

	void updateDynamicModifiers(const std::set<std::string>& majorIdeologies);

  private:
	std::map<std::string, Modifier> dynamicModifiers;
};

} // namespace HoI4



#endif // HOI4_DYNAMIC_MODIFIERS_H