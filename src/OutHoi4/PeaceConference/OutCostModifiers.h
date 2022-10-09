#ifndef SRC_OUTHOI4_PEACECONFERENCE_OUTCOSTMODIFIERS_H
#define SRC_OUTHOI4_PEACECONFERENCE_OUTCOSTMODIFIERS_H



#include <map>
#include <set>
#include <string_view>



namespace HoI4
{

void OutputCostModifiers(std::string_view output_name,
	 const std::set<std::string>& major_ideologies,
	 const std::map<std::string, std::string>& ideologies_to_cost_modifiers);

}



#endif // SRC_OUTHOI4_PEACECONFERENCE_OUTCOSTMODIFIERS_H