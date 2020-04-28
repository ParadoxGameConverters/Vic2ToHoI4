#ifndef HOI4_IDEOLOGICAL_ADVISORS_H_
#define HOI4_IDEOLOGICAL_ADVISORS_H_



#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{
class Advisor;

class IdeologicalAdvisors: commonItems::parser
{
	public:
		IdeologicalAdvisors() noexcept;

		[[nodiscard]] const auto& getAdvisors() const { return theAdvisors; }

	private:
		std::map<std::string, Advisor> theAdvisors;
};

}



#endif // HOI4_IDEOLOGICAL_ADVISORS_H_