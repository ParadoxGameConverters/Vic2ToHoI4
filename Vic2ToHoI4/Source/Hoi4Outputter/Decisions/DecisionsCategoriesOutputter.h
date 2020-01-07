#ifndef DECISIONS_CATEGORIES_OUTPUTTER
#define DECISIONS_CATEGORIES_OUTPUTTER



#include <ostream>
#include <set>
#include <string>



namespace HoI4
{
void outputDecisionCategories(std::ostream& out, const std::set<std::string>& majorIdeologies);
}



#endif // DECISIONS_CATEGORIES_OUTPUTTER
