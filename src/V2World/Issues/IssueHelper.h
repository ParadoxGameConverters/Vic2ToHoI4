#ifndef ISSUE_HELPER_H
#define ISSUE_HELPER_H



#include "external/common_items/ConvenientParser.h"



namespace Vic2
{

class IssueHelper: commonItems::parser
{
  public:
	explicit IssueHelper(std::istream& theStream);

	auto takeIssues() { return std::move(issues); }

  private:
	std::vector<std::string> issues;
};

} // namespace Vic2



#endif // ISSUE_HELPER_H