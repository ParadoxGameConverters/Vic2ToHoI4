#include "PartiesIssueHelper.h"



Vic2::PartiesIssueHelper::PartiesIssueHelper(std::istream& theStream)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& unused, std::istream& theStream) {
		const IssueHelper helper(theStream);
		issues.push_back(helper);
	});

	parseStream(theStream);
}