#include "Issues.h"
#include "../../Configuration.h"
#include "IssueHelper.h"
#include "ParserHelpers.h"
#include "PartiesIssueHelper.h"
#include <vector>



Vic2::Issues Vic2::Issues::Parser::importIssues(const Configuration& theConfiguration)
{
	auto issueNum = 1;
	std::map<int, std::string> issueNames;

	registerKeyword("party_issues", [&issueNames, &issueNum](const std::string& unused, std::istream& theStream) {
		PartiesIssueHelper helperHelper(theStream);
		for (auto& helper: helperHelper.takeIssues())
		{
			for (auto& name: helper.takeIssues())
			{
				issueNames.insert(std::make_pair(issueNum, name));
				issueNum++;
			}
		}
	});
	registerRegex(commonItems::catchallRegex,
		 [&issueNames, &issueNum](const std::string& unused, std::istream& theStream) {
			 IssueHelper helper(theStream);
			 for (auto& name: helper.takeIssues())
			 {
				 issueNames.insert(std::make_pair(issueNum, name));
				 issueNum++;
			 }
		 });

	parseFile(theConfiguration.getVic2Path() + "/common/issues.txt");

	return Issues(issueNames);
}


std::string Vic2::Issues::getIssueName(const int num) const
{
	if (const auto name = issueNames.find(num); name != issueNames.end())
	{
		return name->second;
	}
	else
	{
		return "";
	}
}