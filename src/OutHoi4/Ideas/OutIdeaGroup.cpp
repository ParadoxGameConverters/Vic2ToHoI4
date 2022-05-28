#include "OutIdeaGroup.h"
#include "HOI4World/Ideas/IdeaGroup.h"



std::ostream& HoI4::operator<<(std::ostream& outStream, const IdeaGroup& outIdeaGroup)
{
	outStream << "\t" << outIdeaGroup.name << " = {\n";
	if (outIdeaGroup.law)
	{
		outStream << "\t\tlaw = yes\n";
	}
	if (outIdeaGroup.useListView)
	{
		outStream << "\t\tuse_list_view = yes\n";
	}
	if (outIdeaGroup.designer)
	{
		outStream << "\t\tdesigner = yes\n";
	}
	for (const auto& idea: outIdeaGroup.ideas)
	{
		outStream << "\n";
		outStream << idea;
	}
	outStream << "\t}\n";

	return outStream;
}