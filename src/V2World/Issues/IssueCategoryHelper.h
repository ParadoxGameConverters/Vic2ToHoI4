#ifndef ISSUE_CATEGORY_HELPER_H
#define ISSUE_CATEGORY_HELPER_H



#include "external/common_items/ConvenientParser.h"
#include <string>



namespace Vic2
{

class IssueCategoryHelper: commonItems::parser
{
  public:
	explicit IssueCategoryHelper(std::istream& theStream);

	auto takeIssues() { return std::move(issues); }

  private:
	std::vector<std::string> issues;
};

} // namespace Vic2



#endif // ISSUE_CATEGORY_HELPER_H