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
	const std::filesystem::path folder =
		 std::filesystem::path("output") / theConfiguration.getOutputName() / "common/dynamic_modifiers";
	if (!std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = std::filesystem::path("output") / theConfiguration.getOutputName() /
												  "common/dynamic_modifiers/01_converter_modifiers.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& modifier: dynamicModifiers.getDynamicModifiers() | std::views::values)
	{
		out << modifier << "\n";
	}

	out.close();
}

} // namespace HoI4