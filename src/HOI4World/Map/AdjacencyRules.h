#ifndef HOI4_ADJACENCY_RULES_H
#define HOI4_ADJACENCY_RULES_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Map/AdjacencyRule.h"
#include "src/HOI4World/States/HoI4State.h"
#include <map>



namespace HoI4
{

class AdjacencyRules: commonItems::parser
{
  public:
	explicit AdjacencyRules(const std::map<int, State>& states);

	void importDefaultAdjacencyRules();
	void registerKeywords();
	void updateRules(const std::map<int, State>& states);

	[[nodiscard]] const auto& getRules() const { return rules; }

  private:
	std::map<std::string, std::shared_ptr<AdjacencyRule>> rules;
};

} // namespace HoI4



#endif // HOI4_ADJACENCY_RULES_H