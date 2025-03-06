#ifndef OUT_IDEAS_H
#define OUT_IDEAS_H



#include "src/HOI4World/HoI4Country.h"
#include "src/HOI4World/Ideas/Ideas.h"
#include <set>
#include <string>



namespace HoI4
{

void outIdeas(const Ideas& ideas,
	 const std::set<std::string>& majorIdeologies,
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 const std::filesystem::path& outputName);

} // namespace HoI4



#endif // OUT_IDEAS_H