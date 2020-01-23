#ifndef HOI4_ADVISOR_H
#define HOI4_ADVISOR_H



#include "newParser.h"
#include <string>
#include <vector>



namespace HoI4
{

class Advisor: commonItems::parser
{
	public:
		explicit Advisor(const std::string& ideology, std::istream& theStream);

		[[nodiscard]] const std::vector<std::string>& getTraits() const { return traits; }
		[[nodiscard]] const std::string& getPicture() const { return picture; }
		[[nodiscard]] const std::string& getIdeology() const { return ideology; }

	private:
		std::vector<std::string> traits;
		std::string picture = "";
		std::string ideology = "";
};


struct advisorCompare {
	bool operator() (const Advisor& lhs, const Advisor& rhs) const {
		return lhs.getIdeology() < rhs.getIdeology();
	}
};

}



#endif // HOI4_ADVISOR_H