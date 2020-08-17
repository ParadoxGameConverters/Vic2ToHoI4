#ifndef PARTIES_ISSUE_HELPER_H
#define PARTIES_ISSUE_HELPER_H



#include <string>
#include "Parser.h"



namespace Vic2
{

class PartiesIssueHelper: commonItems::parser
{
  public:
	explicit PartiesIssueHelper(std::istream& theStream);

	auto takeIssues() { return std::move(issues); }

  private:
	std::vector<std::string> issues;
};

} // namespace Vic2



#endif // PARTIES_ISSUE_HELPER_H