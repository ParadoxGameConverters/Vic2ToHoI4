#include "HoI4StatesOutputter.h"
#include "HoI4StateOutputter.h"
#include "../../HOI4World/States/DefaultState.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include <fstream>



void HoI4::outputStates(const States& theStates, const Configuration& theConfiguration)
{
	LOG(LogLevel::Debug) << "Writing states";

	if (!Utils::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/history/states"))
	{
		LOG(LogLevel::Error) << "Could not create \"output/" + theConfiguration.getOutputName() + "/history/states";
		exit(-1);
	}
	for (auto state: theStates.getStates())
	{
		std::string filename("output/" + theConfiguration.getOutputName() + "/history/states/" + std::to_string(state.first) + ".txt");
		std::ofstream out(filename);
		if (!out.is_open())
		{
			std::runtime_error error("Could not open \"" + filename + "\"");
			throw error;
		}
		HoI4::outputHoI4State(out, state.second, theConfiguration);
		out.close();
	}
}