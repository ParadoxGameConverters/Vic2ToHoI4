#ifndef IDEOLOGICAL_DECISIONS_H
#define IDEOLOGICAL_DECISIONS_H



#include "DecisionsInCategory.h"
#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class IdeologicalDecisions: commonItems::parser
{
  public:
	explicit IdeologicalDecisions(std::istream& theStream);

	[[nodiscard]] const auto& getCategories() const { return theCategories; }

	bool requiredIdeologiesExist(const std::set<std::string>& majorIdeologies);

  private:
	std::vector<DecisionsInCategory> theCategories;
	std::set<std::string> requiredIdeologies;
};

} // namespace HoI4



#endif // IDEOLOGICAL_DECISIONS_H