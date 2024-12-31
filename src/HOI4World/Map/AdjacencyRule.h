#ifndef HOI4_ADJACENCY_RULE_H
#define HOI4_ADJACENCY_RULE_H



#include "external/common_items/ConvenientParser.h"
#include <map>
#include <optional>
#include <vector>



namespace HoI4
{

class AdjacencyRule: commonItems::parser
{
  public:
	AdjacencyRule(std::istream& theStream);

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getRules() const { return rules; }
	[[nodiscard]] const auto& getRequiredProvinces() const { return requiredProvinces; }
	[[nodiscard]] const auto& getIsDisabledStr() const { return isDisabledStr; }
	[[nodiscard]] const auto& getIcon() const { return icon; }
	[[nodiscard]] const auto& getOffset() const { return offset; }

	friend std::ostream& operator<<(std::ostream& outStream, const AdjacencyRule& outAdjacencyRule);

  private:
	std::string name;
	std::map<std::string, std::string> rules;
	std::vector<int> requiredProvinces;
	std::optional<std::string> isDisabledStr;
	int icon = 0;
	std::vector<double> offset;
};

} // namespace HoI4



#endif // HOI4_ADJACENCY_RULE_H