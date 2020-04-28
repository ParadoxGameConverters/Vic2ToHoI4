#ifndef ISSUES_H
#define ISSUES_H



#include "Parser.h"
#include <map>
#include <string>



class Configuration;



namespace Vic2
{

class Issues
{
  public:
	class Parser;

	explicit Issues(std::map<int, std::string> issueNames): issueNames(std::move(issueNames)) {}

	[[nodiscard]] std::string getIssueName(int num) const;

  private:
	std::map<int, std::string> issueNames;
};


class Issues::Parser: commonItems::parser
{
  public:
	Issues importIssues(const Configuration& theConfiguration);
};

} // namespace Vic2



#endif // ISSUES_H