#ifndef HOI4_IDEOLOGICAL_ADVISORS_H_
#define HOI4_IDEOLOGICAL_ADVISORS_H_



#include "newParser.h"
#include <map>
#include <string>



namespace HoI4
{
class Advisor;

class IdeologicalAdvisors: commonItems::parser
{
	public:
		IdeologicalAdvisors() noexcept;

		auto getAdvisors() { return theAdvisors; }

	private:
		std::map<std::string, HoI4::Advisor> theAdvisors;
};

}



#endif // HOI4_IDEOLOGICAL_ADVISORS_H_