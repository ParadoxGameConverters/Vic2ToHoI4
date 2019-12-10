#ifndef HOI4_DECISIONS_CATEGORIES_H
#define HOI4_DECISIONS_CATEGORIES_H



#include "newParser.h"
#include <set>
#include <string>



namespace HoI4
{

class DecisionsCategories
{
	public:
		explicit DecisionsCategories(
			std::set<std::string> _majorIdeologies
		):	majorIdeologies(std::move(_majorIdeologies)) {}

		friend std::ostream& operator<<(std::ostream& out, const DecisionsCategories& theCategories);

	private:
		std::set<std::string> majorIdeologies;
};

}


#endif // HOI4_DECISIONS_CATEGORIES_H