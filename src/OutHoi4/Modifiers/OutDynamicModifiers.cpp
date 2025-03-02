#include "src/OutHoi4/Modifiers/OutDynamicModifiers.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/HOI4World/Modifiers/DynamicModifiers.h"
#include "src/HOI4World/Modifiers/Modifier.h"
#include <fstream>
#include <ranges>


namespace HoI4
{

void outDynamicModifiers(const DynamicModifiers& dynamicModifiers, const Configuration& theConfiguration)
{
	if (!commonItems::TryCreateFolder("output/" + theConfiguration.getOutputName() + "/common/dynamic_modifiers"))
	{
		throw std::runtime_error(
			 "Could not create output/" + theConfiguration.getOutputName() + "/common/dynamic_modifiers/");
	}

	std::ofstream out(
		 "output/" + theConfiguration.getOutputName() + "/common/dynamic_modifiers/01_converter_modifiers.txt");
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create 01_converter_modifiers.txt.");
	}

	for (const auto& modifier: dynamicModifiers.getDynamicModifiers() | std::views::values)
	{
		out << modifier << "\n";
	}

	out.close();
}

} // namespace HoI4