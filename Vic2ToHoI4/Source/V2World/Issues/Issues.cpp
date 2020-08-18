#include "Issues.h"



std::string Vic2::Issues::getIssueName(const unsigned int num) const
{
	if (num > issueNames.size() || num < 1)
	{
		return "";
	}

	return issueNames[num - 1];
}