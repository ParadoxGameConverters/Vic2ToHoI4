#ifndef HOI4_DIVISION_H_
#define HOI4_DIVISION_H_



#include <ostream>
#include <string>



namespace HoI4
{

class DivisionType
{
	public:
		DivisionType(const std::string& name, const std::string& type, int location, double experience);
		DivisionType(const DivisionType&) = default;

		friend std::ostream& operator << (std::ostream& out, const DivisionType&);

	private:
		DivisionType& operator=(const DivisionType&) = delete;

		std::string	name;
		std::string	type;
		int location = 0;
		double experience;
};

}



#endif // HOI4_DIVISION_H_