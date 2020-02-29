#ifndef OUT_IDEAS_H
#define OUT_IDEAS_H



#include <set>
#include <string>
#include "../../Configuration.h"


namespace HoI4
{

class Ideas;

void outIdeas(const Ideas& ideas, const std::set<std::string>& majorIdeologies, const Configuration& theConfiguration);

}





#endif // OUT_IDEAS_H