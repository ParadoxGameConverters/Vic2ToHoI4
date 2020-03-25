#ifndef OUT_DECISIONS_CATEGORIES_H
#define OUT_DECISIONS_CATEGORIES_H



#include <ostream>
#include <set>
#include <string>



namespace HoI4
{

void outputDecisionCategories(std::ostream& out, const std::set<std::string>& majorIdeologies);

}



#endif // OUT_DECISIONS_CATEGORIES_H
