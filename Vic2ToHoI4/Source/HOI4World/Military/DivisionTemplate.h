#ifndef HOI4_DIVISION_TEMPLATE_H_
#define HOI4_DIVISION_TEMPLATE_H_



#include "newParser.h"
#include "Regiment.h"
#include <istream>
#include <ostream>
#include <string>
#include <vector>



namespace HoI4
{


class DivisionTemplateType: commonItems::parser
{
	public:
		explicit DivisionTemplateType(std::istream& theStream);
		DivisionTemplateType(const DivisionTemplateType&) = default;
		DivisionTemplateType& operator=(const DivisionTemplateType&) = delete;

		bool operator==(const std::string& rhs) const { return name == rhs; }

		friend std::ostream& operator << (std::ostream& out, const DivisionTemplateType& rhs);

		std::string getName() const { return name; }
		std::vector<RegimentType> getRegiments() const { return regiments; }
		std::vector<RegimentType> getSupportRegiments() const { return supportRegiments; }

	private:
		std::string name;
		std::vector<RegimentType> regiments;
		std::vector<RegimentType> supportRegiments;
};

}



#endif // HOI4_DIVISION_TEMPLATE_H_
