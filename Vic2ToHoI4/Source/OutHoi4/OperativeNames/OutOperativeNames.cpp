#include "OutOperativeNames.h"
#include "OSCompatibilityLayer.h"
#include "OutOperativeNamesSet.h"



void HoI4::outputOperativeNames(const OperativeNames& operativeNames, const std::string& outputName)
{
	commonItems::TryCreateFolder("output/" + outputName + "/common/units/codenames_operatives/");
	for (const auto& operativeNamesSet: operativeNames.getOperativeNamesSets())
	{
		outputOperativeNamesSet(operativeNamesSet.second, outputName);
	}
}