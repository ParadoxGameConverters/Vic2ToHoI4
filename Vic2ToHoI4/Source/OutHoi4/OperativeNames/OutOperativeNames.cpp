#include "OutOperativeNames.h"
#include "OSCompatibilityLayer.h"
#include "OutOperativeNamesSet.h"
#include <ranges>



void HoI4::outputOperativeNames(const OperativeNames& operativeNames, const std::string& outputName)
{
	commonItems::TryCreateFolder("output/" + outputName + "/common/units/codenames_operatives/");
	for (const auto& operativeNamesSet: operativeNames.getOperativeNamesSets() | std::views::values)
	{
		outputOperativeNamesSet(operativeNamesSet, outputName);
	}
}