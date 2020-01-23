#ifndef HOI4_ADVISOR_H
#define HOI4_ADVISOR_H



#include "newParser.h"
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <vector>



namespace HoI4
{

class Advisor: commonItems::parser
{
	public:
		explicit Advisor(const std::string& ideology, std::istream& theStream);

		const std::vector<std::string>& getTraits() const { return traits; }
		const std::string& getPicture() const { return picture; }
		const std::string& getIdeology() const { return ideology; }

	private:
		std::vector<std::string> traits;
		std::string picture = "";
		std::string ideology = "";
};


struct advisorCompare {
	bool operator() (const HoI4::Advisor& lhs, const HoI4::Advisor& rhs) const {
		return lhs.getIdeology() < rhs.getIdeology();
	}
};

}



#endif // HOI4_ADVISOR_H