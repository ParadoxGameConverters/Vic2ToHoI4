#include "Pop.h"



float Vic2::Pop::getIssueSupport(const std::string& issueName) const
{
	if (!popIssues.contains(issueName))
	{
		return 0.0F;
	}

	return popIssues.at(issueName);
}