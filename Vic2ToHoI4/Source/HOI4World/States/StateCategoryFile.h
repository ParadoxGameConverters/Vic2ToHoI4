#ifndef HOI4_STATE_CATEGORY_FILE_H
#define HOI4_STATE_CATEGORY_FILE_H



#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class StateCategoryFile: commonItems::parser
{
	public:
		explicit StateCategoryFile(std::istream& theStream);

		auto getCategories() const { return theCategories; }

	private:
		std::map<int, std::string> theCategories;
};

}



#endif // HOI4_STATE_CATEGORY_FILE_H