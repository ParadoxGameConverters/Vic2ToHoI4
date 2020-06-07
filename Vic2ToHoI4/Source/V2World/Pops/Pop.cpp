#include "Pop.h"
#include "../Issues/Issues.h"



float Vic2::Pop::getIssue(const std::string& issueName) const
{
	if (const auto& issue = popIssues.find(issueName); issue != popIssues.end())
	{
		return issue->second;
	}
	else
	{
		return 0.0f;
	}
}