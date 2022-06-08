#ifndef HOI4_IDEOLOGICAL_ADVISORS_H_
#define HOI4_IDEOLOGICAL_ADVISORS_H_



#include "src/HOI4World/Leaders/Advisor.h"
#include "external/common_items/ConvenientParser.h"
#include <map>
#include <string>



namespace HoI4
{

class IdeologicalAdvisors: commonItems::parser
{
  public:
	IdeologicalAdvisors() noexcept;

	[[nodiscard]] const auto& getAdvisors() const { return theAdvisors; }

  private:
	std::map<std::string, Advisor> theAdvisors;
};

} // namespace HoI4



#endif // HOI4_IDEOLOGICAL_ADVISORS_H_