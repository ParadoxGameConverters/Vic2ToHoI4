#include "OutHoI4States.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "OutHoI4State.h"
#include <fstream>



void HoI4::outputStates(const States& theStates, const std::string& outputName, const bool debugEnabled)
{
	LOG(LogLevel::Debug) << "Writing states";

	if (!Utils::TryCreateFolder("output/" + outputName + "/history/states"))
	{
		throw std::runtime_error("Could not create \"output/" + outputName + "/history/states");
	}
	for (const auto& state: theStates.getStates())
	{
		auto filename("output/" + outputName + "/history/states/" + std::to_string(state.first) + ".txt");
		std::ofstream out(filename);
		if (!out.is_open())
		{
			throw std::runtime_error("Could not open \"" + filename + "\"");
		}
		outputHoI4State(out, state.second, debugEnabled);
		out.close();
	}
}