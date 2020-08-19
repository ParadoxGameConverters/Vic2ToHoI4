#include "OutScriptedEffects.h"
#include <fstream>



void HoI4::outputScriptedEffects(const std::string& outputName)
{
	std::ofstream scriptedEffects("output/" + outputName + "/common/scripted_effects/00_scripted_effects.txt",
		 std::ios::app);
	if (!scriptedEffects.is_open())
	{
		throw std::runtime_error(
			 "Could not open output/" + outputName + "/common/scripted_effects/00_scripted_effects.txt");
	}

	scriptedEffects << "test_output";
	scriptedEffects.close();
}