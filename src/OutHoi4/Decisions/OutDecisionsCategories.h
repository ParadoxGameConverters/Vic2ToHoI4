#ifndef OUT_DECISIONS_CATEGORIES_H
#define OUT_DECISIONS_CATEGORIES_H



#include "src/HOI4World/Decisions/DecisionsCategories.h"
#include <string>



namespace HoI4
{

void outputDecisionCategories(const std::filesystem::path& filename, const DecisionsCategories& categories);

}



#endif // OUT_DECISIONS_CATEGORIES_H
