#ifndef ISSUE_HELPER_H
#define ISSUE_HELPER_H



#include "newParser.h"



namespace Vic2
{

class IssueHelper: commonItems::parser
{
  public:
	explicit IssueHelper(std::istream& theStream);

	std::vector<std::string> getIssues() { return issues; }

  private:
	std::vector<std::string> issues;
};

} // namespace Vic2



#endif // ISSUE_HELPER_H