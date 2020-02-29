#include "OutIdeaGroup.h"
#include "../../HOI4World/Ideas/IdeaGroup.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const HoI4::IdeaGroup& outIdeaGroup)
{
	outStream << "	" << outIdeaGroup.name << " = {\n";
	if (outIdeaGroup.law)
	{
		outStream << "		law = yes\n";
	}
	if (outIdeaGroup.designer)
	{
		outStream << "		designer = yes\n";
	}
	for (auto idea : outIdeaGroup.ideas)
	{
		outStream << "\n";
		outStream << idea;
	}
	outStream << "	}\n";

	return outStream;
}