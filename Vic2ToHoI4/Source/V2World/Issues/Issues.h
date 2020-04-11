#ifndef ISSUES_H
#define ISSUES_H



#include "newParser.h"
#include <map>
#include <memory>
#include <string>



class Configuration;



namespace Vic2
{

class Issues: commonItems::parser
{
  public:
	void instantiate(const Configuration& theConfiguration);
	std::string getIssueName(int num) const;

  private:
	std::map<int, std::string> issueNames;
};

} // namespace Vic2



#endif // ISSUES_H