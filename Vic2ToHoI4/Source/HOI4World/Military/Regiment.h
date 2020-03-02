#ifndef HOI4_REGIMENT_H
#define HOI4_REGIMENT_H



#include "newParser.h"
#include <istream>
#include <ostream>
#include <string>



namespace HoI4
{

class RegimentType: commonItems::parser
{
	public:
		explicit RegimentType(const std::string& _type, std::istream& theStream);
		RegimentType(const RegimentType&) = default;

		const std::string getType() const { return type; }

		friend std::ostream& operator << (std::ostream& out, const RegimentType& regiment);

	private:
		RegimentType& operator=(const RegimentType&) = delete;

		std::string	type;
		int x = 0;
		int y = 0;
};


std::ostream& operator << (std::ostream& out, const RegimentType& regiment);

}



#endif // HOI4_REGIMENT_H
