#include "Pop.h"



float Vic2::Pop::getIssueSupport(const std::string& issueName) const
{
	if (const auto& issue = popIssues.find(issueName); issue != popIssues.end())
	{
		return issue->second;
	}
	else
	{
		return 0.0F;
	}
}