#include "src/V2World/Pops/Pop.h"



float Vic2::Pop::getIssueSupport(const std::string& issueName) const
{
	if (!popIssues_.contains(issueName))
	{
		return 0.0F;
	}

	return popIssues_.at(issueName);
}