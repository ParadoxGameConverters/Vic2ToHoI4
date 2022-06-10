#include "src/V2World/Issues/IssueCategoryHelper.h"
#include "external/common_items/CommonRegexes.h"
#include "src/V2World/Issues/IssueHelper.h"



Vic2::IssueCategoryHelper::IssueCategoryHelper(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		for (const auto& issue: IssueHelper(theStream).takeIssues())
		{
			issues.push_back(issue);
		}
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}