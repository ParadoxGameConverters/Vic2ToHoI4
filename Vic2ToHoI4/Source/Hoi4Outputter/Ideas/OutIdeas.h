#ifndef OUT_IDEAS_H
#define OUT_IDEAS_H



#include "../../Configuration.h"
#include <set>
#include <string>



namespace HoI4
{

class Ideas;

void outIdeas(const Ideas& ideas, const std::set<std::string>& majorIdeologies, const Configuration& theConfiguration);

} // namespace HoI4



#endif // OUT_IDEAS_H