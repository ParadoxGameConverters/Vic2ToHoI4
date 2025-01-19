#include "src/OutHoi4/Map/OutAdjacencyRule.h"
#include "src/HOI4World/Map/AdjacencyRule.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const AdjacencyRule& outAdjacencyRule)
{
	outStream << "adjacency_rule =\n";
	outStream << "{\n";
	outStream << "\tname = \"" << outAdjacencyRule.name << "\"\n";
	outStream << "\n";

	for (const auto& [ruleName, rule]: outAdjacencyRule.rules)
	{
		outStream << "\t" << ruleName << " " << rule << "\n";
	}
	outStream << "\n";

	outStream << "\trequired_provinces = { ";
	for (const auto& province: outAdjacencyRule.requiredProvinces)
	{
		outStream << province << " ";
	}
	outStream << "}\n";
	outStream << "\n";

	if (outAdjacencyRule.isDisabledStr)
	{
		outStream << "\tis_disabled " << *outAdjacencyRule.isDisabledStr << "\n";
		outStream << "\n";
	}
	outStream << "\ticon = " << outAdjacencyRule.icon << "\n";

	outStream << "\toffset = { ";
	for (const auto& offset: outAdjacencyRule.offset)
	{
		outStream << offset << " ";
	}
	outStream << "}\n";
	outStream << "}\n";
	outStream << "\n";

	return outStream;
}