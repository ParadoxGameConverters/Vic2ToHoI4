#include "PartiesIssueHelper.h"



Vic2::PartiesIssueHelper::PartiesIssueHelper(std::istream& theStream)
{
	registerRegex("[A-Za-z_]+", [this](const std::string& theIssue, std::istream& theStream) {
		IssueHelper helper(theStream);
		issues.push_back(helper);
	});

	parseStream(theStream);
}