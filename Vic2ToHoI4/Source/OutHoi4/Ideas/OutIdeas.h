#ifndef OUT_IDEAS_H
#define OUT_IDEAS_H



#include "Configuration.h"
#include "HOI4World/Ideas/Ideas.h"
#include <set>
#include <string>



namespace HoI4
{

void outIdeas(const Ideas& ideas, const std::set<std::string>& majorIdeologies, const std::string& outputName);

} // namespace HoI4



#endif // OUT_IDEAS_H