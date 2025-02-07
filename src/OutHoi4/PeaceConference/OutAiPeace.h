#ifndef SRC_OUTHOI4_PEACECONFERENCE_OUTAIPEACE_H
#define SRC_OUTHOI4_PEACECONFERENCE_OUTAIPEACE_H



#include <map>
#include <set>
#include <string_view>
#include <vector>



namespace HoI4
{

void OutputAiPeace(std::filesystem::path output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_to_ai_peace,
	 const std::vector<std::string>& dynamic_ai_peaces);

}



#endif // SRC_OUTHOI4_PEACECONFERENCE_OUTAIPEACE_H