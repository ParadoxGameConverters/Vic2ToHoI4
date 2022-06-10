#ifndef ISSUES_BUILDER_H
#define ISSUES_BUILDER_H



#include "src/V2World/Issues/Issues.h"
#include <memory>



namespace Vic2
{

class Issues::Builder
{
  public:
	Builder() { issues = std::make_unique<Issues>(); }
	std::unique_ptr<Issues> build() { return std::move(issues); }

	Builder& setIssueNames(std::vector<std::string> issueNames)
	{
		issues->issueNames = std::move(issueNames);
		return *this;
	}

	Builder& addIssueName(std::string issueName)
	{
		issues->issueNames.push_back(std::move(issueName));
		return *this;
	}

  private:
	std::unique_ptr<Issues> issues;
};

} // namespace Vic2



#endif // ISSUES_BUILDER_H