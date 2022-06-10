#ifndef ISSUES_FACTORY_H
#define ISSUES_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/V2World/Issues/Issues.h"
#include <memory>



namespace Vic2
{

class Issues::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<Issues> getIssues(const std::string& vic2Path);

  private:
	std::unique_ptr<Issues> issues;
};

} // namespace Vic2



#endif // ISSUES_FACTORY_H