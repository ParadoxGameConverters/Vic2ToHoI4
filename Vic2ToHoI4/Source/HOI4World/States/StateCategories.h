#ifndef HOI4_STATE_CATEGORIES_H
#define HOI4_STATE_CATEGORIES_H



#include "newParser.h"
#include <map>
#include <string>



namespace HoI4
{

class StateCategories: commonItems::parser
{
	public:
		StateCategories();
		virtual ~StateCategories() = default;

		virtual std::string getBestCategory(int numBuildingSlots) const;

	private:
		std::map<int, std::string> theCategories;
};

}



#endif // HOI4_STATE_CATEGORIES_H
