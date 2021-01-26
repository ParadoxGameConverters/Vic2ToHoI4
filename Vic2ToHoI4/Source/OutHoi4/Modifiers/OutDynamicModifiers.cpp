#include "OutDynamicModifiers.h"
#include "HOI4World/Modifiers/DynamicModifiers.h"
#include "HOI4World/Modifiers/Modifier.h"
#include "OSCompatibilityLayer.h"
#include <fstream>

namespace HoI4
{

void outDynamicModifiers(const DynamicModifiers& dynamicModifiers, const Configuration& theConfiguration)
{
	if (!commonItems::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/dynamic_modifiers"))
	{
		Log(LogLevel::Error) << "Could not create output/" + theConfiguration.getOutputName() +
											 "/common/dynamic_modifiers/";
		exit(-1);
	}

	std::ofstream out(
		 "output/" + theConfiguration.getOutputName() + "/common/dynamic_modifiers/01_converter_modifiers.txt");
	if (!out.is_open())
	{
		LOG(LogLevel::Error) << "Could not create 01_converter_modifiers.txt.";
		exit(-1);
	}

	for (const auto& [unused, modifier]: dynamicModifiers.getDynamicModifiers())
	{
		out << modifier << "\n";
	}

	out.close();
}

} // namespace HoI4