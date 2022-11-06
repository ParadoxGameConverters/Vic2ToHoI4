#ifndef SRC_HOI4WORLD_PEACECONFERENCES_H
#define SRC_HOI4WORLD_PEACECONFERENCES_H



#include <set>
#include <string>
#include <vector>



namespace HoI4
{


std::vector<std::string> GenerateDynamicAiPeaces(const std::set<std::string>& major_ideologies);


} // namespace HoI4



#endif // SRC_HOI4WORLD_PEACECONFERENCES_H