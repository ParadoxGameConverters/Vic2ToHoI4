#ifndef ISSUES_H
#define ISSUES_H



#include "Parser.h"
#include <string>
#include <vector>



class Configuration;



namespace Vic2
{

class Issues
{
  public:
	class Builder;
	class Factory;
	Issues() = default;

	[[nodiscard]] std::string getIssueName(unsigned int num) const;

  private:
	std::vector<std::string> issueNames;
};

} // namespace Vic2



#endif // ISSUES_H