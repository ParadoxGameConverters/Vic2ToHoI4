#include "src/OutHoi4/States/OutHoI4States.h"
#include "external/common_items/Log.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/States/OutHoI4State.h"
#include <fstream>



void HoI4::outputStates(const States& theStates, const std::filesystem::path& outputName, const bool debugEnabled)
{
	Log(LogLevel::Info) << "\t\tWriting states";

	std::filesystem::path history_folder = "output" / outputName / "history/states";
	if (!commonItems::DoesFolderExist(history_folder) && !std::filesystem::create_directories(history_folder))
	{
		throw std::runtime_error("Could not create " + outputName.string());
	}
	for (const auto& state: theStates.getStates())
	{
		std::filesystem::path filename = history_folder / std::to_string(state.first);
		filename += ".txt";
		std::ofstream out(filename);
		if (!out.is_open())
		{
			throw std::runtime_error("Could not open " + filename.string());
		}
		outputHoI4State(out, state.second, debugEnabled);
		out.close();
	}

	auto filename("output" / outputName / "common/scripted_triggers/state_triggers_FR_loc.txt");
	std::ofstream out(filename);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not open " + filename.string());
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