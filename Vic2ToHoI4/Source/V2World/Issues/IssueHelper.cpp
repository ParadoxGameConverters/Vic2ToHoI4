#include "IssueHelper.h"
#include "ParserHelpers.h"



Vic2::IssueHelper::IssueHelper(std::istream& theStream)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& theIssue, std::istream& theStream) {
		issues.push_back(theIssue);
		commonItems::ignoreObject(theIssue, theStream);
	});

	parseStream(theStream);
}