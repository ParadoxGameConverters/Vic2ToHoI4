#include "OccupationLaws.h"
#include <algorithm>



void HoI4::OccupationLaws::updateLaws(const std::set<std::string>& majorIdeologies)
{
	occupationLaws.erase(std::remove_if(occupationLaws.begin(),
									 occupationLaws.end(),
									 [](const OccupationLaw& law) {
										 return law.getName() == "reconciliation";
									 }),
		 occupationLaws.end());

	if (!majorIdeologies.contains("democratic"))
	{
		occupationLaws.erase(std::remove_if(occupationLaws.begin(),
										 occupationLaws.end(),
										 [](const OccupationLaw& law) {
											 return law.getName() == "autonomous_occupation";
										 }),
			 occupationLaws.end());

		auto noGarrisonLaw = std::find_if(occupationLaws.begin(), occupationLaws.end(), [](const OccupationLaw& law) {
			return law.getName() == "no_garrison";
		});
		if (noGarrisonLaw != occupationLaws.end())
		{
			noGarrisonLaw->setAiWillDo(
				 "= {\n"
				 "\t\tbase = 0\n"
				 "\n"
				 "\t\t# if losing, get manpower & equipment back\n"
				 "\t\tmodifier = {\n"
				 "\t\t\tFROM = {\n"
				 "\t\t\t\tsurrender_progress > 0.15\n"
				 "\t\t\t}\n"
				 "\t\t\tadd = 100\n"
				 "\t\t}\n"
				 "\t\tmodifier = {\n"
				 "\t\t\tFROM = {\n"
				 "\t\t\t\tsurrender_progress > 0.4\n"
				 "\t\t\t}\n"
				 "\t\t\tadd = 500\n"
				 "\t\t}\n"
				 "\t}");
		}
	}

	if (!majorIdeologies.contains("communism"))
	{
		occupationLaws.erase(std::remove_if(occupationLaws.begin(),
										 occupationLaws.end(),
										 [](const OccupationLaw& law) {
											 return law.getName() == "liberate_workers_occupation";
										 }),
			 occupationLaws.end());
	}

	if (!majorIdeologies.contains("fascism"))
	{
		occupationLaws.erase(std::remove_if(occupationLaws.begin(),
										 occupationLaws.end(),
										 [](const OccupationLaw& law) {
											 return law.getName() == "brutally_oppressive_occupation";
										 }),
			 occupationLaws.end());
	}
}