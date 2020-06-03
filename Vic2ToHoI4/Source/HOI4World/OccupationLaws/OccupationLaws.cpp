#include "OccupationLaws.h"
#include <algorithm>



void HoI4::OccupationLaws::updateLaws(const std::set<std::string>& majorIdeologies)
{
	if (!majorIdeologies.count("democratic"))
	{
		occupationLaws.erase(std::remove_if(occupationLaws.begin(),
										 occupationLaws.end(),
										 [](const OccupationLaw& law) {
											 return law.getName() == "autonomous_occupation";
										 }),
			 occupationLaws.end());
	}

	if (!majorIdeologies.count("communism"))
	{
		occupationLaws.erase(std::remove_if(occupationLaws.begin(),
										 occupationLaws.end(),
										 [](const OccupationLaw& law) {
											 return law.getName() == "liberate_workers_occupation";
										 }),
			 occupationLaws.end());
	}
}