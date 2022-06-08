#include "src/OutHoi4/Decisions/OutDecisionsInCategory.h"
#include "src/OutHoi4/Decisions/OutDecision.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const DecisionsInCategory& outCategory)
{
	outStream << outCategory.name << " = {\n";
	for (const auto& decision: outCategory.theDecisions)
	{
		outStream << decision << "\n";
	}
	if (outCategory.theDecisions.empty())
	{
		outStream << "\n";
	}
	outStream << "}\n";
	outStream << "\n";

	return outStream;
}