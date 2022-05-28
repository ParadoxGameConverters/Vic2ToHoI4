#ifndef ISSUES_H
#define ISSUES_H



#include <string>
#include <vector>



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