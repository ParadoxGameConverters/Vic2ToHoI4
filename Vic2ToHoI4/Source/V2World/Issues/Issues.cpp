#include "Issues.h"
#include "../../Configuration.h"
#include "IssueHelper.h"
#include "ParserHelpers.h"
#include "PartiesIssueHelper.h"
#include <vector>



Vic2::Issues Vic2::Issues::Parser::importIssues(const Configuration& theConfiguration)
{
	int issueNum = 1;
	std::map<int, std::string> issueNames;

	registerKeyword("party_issues", [&issueNames, &issueNum](const std::string& category, std::istream& theStream) {
		PartiesIssueHelper helperHelper(theStream);
		for (auto helper: helperHelper.getIssues())
		{
			for (auto name: helper.getIssues())
			{
				issueNames.insert(make_pair(issueNum, name));
				issueNum++;
			}
		}
	});
	registerKeyword("[A-Za-z_]+", [&issueNames, &issueNum](const std::string& category, std::istream& theStream) {
		IssueHelper helper(theStream);
		for (auto name: helper.getIssues())
		{
			issueNames.insert(make_pair(issueNum, name));
			issueNum++;
		}
	});

	parseFile(theConfiguration.getVic2Path() + "/common/issues.txt");

	return Issues(issueNames);
}


std::string Vic2::Issues::getIssueName(int num) const
{
	auto name = issueNames.find(num);
	if (name != issueNames.end())
	{
		return name->second;
	}
	else
	{
		return "";
	}
}