#ifndef ISSUES_H
#define ISSUES_H



#include "newParser.h"
#include <map>
#include <memory>
#include <string>



class Configuration;



namespace Vic2
{

class Issues
{
  public:
	class Parser;

	Issues(std::map<int, std::string> issueNames): issueNames(std::move(issueNames)) {}

	std::string getIssueName(int num) const;

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