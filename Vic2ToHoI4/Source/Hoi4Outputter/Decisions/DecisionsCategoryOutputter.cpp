#include "DecisionsCategoryOutputter.h"
#include "DecisionOutputter.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const decisionsCategory& outCategory)
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