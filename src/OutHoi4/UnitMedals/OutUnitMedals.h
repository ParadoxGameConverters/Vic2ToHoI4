#ifndef SRC_OUTHOI4_UNITMEDALS_OUTUNITMEDALS_H
#define SRC_OUTHOI4_UNITMEDALS_OUTUNITMEDALS_H



#include <map>
#include <set>
#include <string_view>



namespace HoI4
{

void OutputUnitMedals(std::filesystem::path output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_unit_medals);

}



#endif // SRC_OUTHOI4_UNITMEDALS_OUTUNITMEDALS_H