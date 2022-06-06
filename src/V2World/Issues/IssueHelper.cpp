#include "IssueHelper.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::IssueHelper::IssueHelper(std::istream& theStream)
{
	registerKeyword("administrative", commonItems::ignoreItem);
	registerKeyword("next_step_only", commonItems::ignoreItem);
	registerRegex(commonItems::catchallRegex, [this](const std::string& theIssue, std::istream& theStream) {
		issues.push_back(theIssue);
		commonItems::ignoreObject(theIssue, theStream);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}