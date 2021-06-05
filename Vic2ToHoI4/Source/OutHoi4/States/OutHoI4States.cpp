#include "OutHoI4States.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "OutHoI4State.h"
#include <fstream>



void HoI4::outputStates(const States& theStates, const std::string& outputName, const bool debugEnabled)
{
	Log(LogLevel::Info) << "\t\tWriting states";

	if (!commonItems::TryCreateFolder("output/" + outputName + "/history/states"))
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

	auto filename("output/" + outputName + "/common/scripted_triggers/state_triggers_FR_loc.txt");
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open \"" + filename + "\"");
	}
	for (const auto& [category, stateIds]: theStates.getLanguageCategories())
	{
		if (category.empty())
		{
			if (debugEnabled)
			{
				Log warning(LogLevel::Warning);
				warning << "No language category defined for HoI4 states:";
				for (const auto& id: stateIds)
				{
					warning << " " << id;
				}
			}
			continue;
		}

		out << category << " = {\n";
		out << "\tOR = {\n";
		for (const auto& id: stateIds)
		{
			out << "\t\tstate = " << id << "\n";
		}
		out << "\t}\n";
		out << "}\n";
	}
	out.close();
}