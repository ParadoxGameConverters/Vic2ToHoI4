#include "Issues.h"
#include "../Configuration.h"
#include "ParserHelpers.h"
#include <vector>



class issueHelper: commonItems::parser
{
	public:
		explicit issueHelper(std::istream& theStream);

		std::vector<std::string> getIssues() { return issues; }

	private:
		std::vector<std::string> issues;
};


class partiesIssueHelper: commonItems::parser
{
	public:
		explicit partiesIssueHelper(std::istream& theStream);

		std::vector<issueHelper> getIssues() { return issues; }

	private:
		std::vector<issueHelper> issues;
};



void Vic2::Issues::instantiate()
{
	int issueNum = 1;

	registerKeyword(std::regex("party_issues"), [this, &issueNum](const std::string& category, std::istream& theStream)
	{
		partiesIssueHelper helperHelper(theStream);
		for (auto helper: helperHelper.getIssues())
		{
			for (auto name: helper.getIssues())
			{
				issueNames.insert(make_pair(issueNum, name));
				issueNum++;
			}
		}
	});
	registerKeyword(std::regex("[A-Za-z_]+"), [this, &issueNum](const std::string& category, std::istream& theStream)
	{
		issueHelper helper(theStream);
		for (auto name: helper.getIssues())
		{
			issueNames.insert(make_pair(issueNum, name));
			issueNum++;
		}
	});

	parseFile(theConfiguration.getVic2Path() + "/common/issues.txt");
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


issueHelper::issueHelper(std::istream& theStream)
{
	registerKeyword(std::regex("[A-Za-z_]+"), [this](const std::string& theIssue, std::istream& theStream)
	{
		issues.push_back(theIssue);
		commonItems::ignoreObject(theIssue, theStream);
	});

	parseStream(theStream);
}


partiesIssueHelper::partiesIssueHelper(std::istream& theStream)
{
	registerKeyword(std::regex("[A-Za-z_]+"), [this](const std::string& theIssue, std::istream& theStream)
	{
		issueHelper helper(theStream);
		issues.push_back(helper);
	});

	parseStream(theStream);
}