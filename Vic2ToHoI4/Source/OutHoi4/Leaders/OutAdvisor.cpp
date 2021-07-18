#include "OutAdvisor.h"



void HoI4::outputAdvisor(std::ostream& output, const std::string& tag, const Advisor& theAdvisor)
{
	output << "\t\t" << tag << "_" << theAdvisor.getIdeology() << "_advisor = {\n";
	output << "\t\t\tallowed = {\n";
	output << "\t\t\t\toriginal_tag = \"" << tag << "\"\n";
	output << "\t\t\t}\n";
	output << "\t\t\ttraits = { ";
	for (const auto& trait: theAdvisor.getTraits())
	{
		output << trait << " ";
	}
	output << "}\n";
	if (!theAdvisor.getPicture().empty())
	{
		output << "\t\t\tpicture = \"" << theAdvisor.getPicture() << "\"\n";
	}
	output << "\t\t\tdo_effect = {\n";
	output << "\t\t\t\tNOT = {\n";
	output << "\t\t\t\t\thas_government = " << theAdvisor.getIdeology() << "\n";
	output << "\t\t\t\t}\n";
	output << "\t\t\t}\n";
	output << "\t\t\tai_will_do = {\n";
	output << "\t\t\t\tfactor = 0\n";
	output << "\t\t\t}\n";
	output << "\t\t}\n";
}